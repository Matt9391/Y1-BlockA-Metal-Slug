#include "precomp.h"
#include "PlayerState.h"

// ---------------------------------------------------------------------------
// How the inputs behave (see Player::getPlayerInput), because every rule below
// depends on it:
//   isShooting / isJumping  -> true for ONE tick (isKeyJustPressed). If a state
//                              doesn't react to the pulse on that tick, the
//                              shot/jump animation is lost forever.
//   onAnimationEnd          -> true while the clip sits on its LAST frame.
//   isCrouching == inputDown
//
// Rules every state follows:
//   1. dead always wins.
//   2. Grounded states: !isGrounded -> falling, jump pulse -> jump.
//      (Crouch + shoot never jumps: Player::handleMovement blocks it, so the
//      animation must not show a jump either.)
//   3. Air states: isGrounded -> landing.
//   4. A shoot pulse always picks the animation that matches what
//      Player::update actually fires (melee vs bullet, aim up / down / forward).
//   5. onAnimationEnd is checked last, so real input interrupts a clip.
// ---------------------------------------------------------------------------
namespace
{
    // "no transition decided" marker for the helpers below
    const PlayerAnimationSet NO_CHANGE = PlayerAnimationSet::PAS_COUNTS;

    // A shot pulse while standing/walking/crouching.
    // enemyInFront -> melee (Player::update fires no bullet),
    // W held       -> aim up (Player::update sets shoot dir up),
    // S held       -> crouch shot (S is only "down" when grounded).
    PlayerAnimationSet groundShoot(const PlayerInput& in)
    {
        if (in.enemyInFront) return in.isMoving ? PlayerAnimationSet::PAS_MELEE_ATTACK_WALK
                                                : PlayerAnimationSet::PAS_MELEE_ATTACK_IDLE;
        if (in.inputUp)      return in.isMoving ? PlayerAnimationSet::PAS_SHOOTING_WALK_UP
                                                : PlayerAnimationSet::PAS_SHOOTING_IDLE_UP;
        if (in.isCrouching)  return PlayerAnimationSet::PAS_SHOOTING_CROUCH;
        return in.isMoving ? PlayerAnimationSet::PAS_SHOOTING_WALK
                           : PlayerAnimationSet::PAS_SHOOTING_IDLE;
    }

    // A shot pulse in the air. `forward` is true for the *Forward states.
    // Up/down always win because that is the direction the bullet really goes.
    PlayerAnimationSet airShoot(const PlayerInput& in, bool forward)
    {
        if (in.inputUp)   return PlayerAnimationSet::PAS_SHOOTING_UP_JUMP_UP;
        if (in.inputDown) return PlayerAnimationSet::PAS_SHOOTING_JUMP_DOWN;
        return forward ? PlayerAnimationSet::PAS_SHOOTING_JUMP_FORWARD
                       : PlayerAnimationSet::PAS_SHOOTING_JUMP_UP;
    }

    // Where to go the moment we touch the ground (or a clip ends on the ground).
    PlayerAnimationSet landing(const PlayerInput& in)
    {
        if (in.isShooting)  return groundShoot(in);
        if (in.isCrouching) return in.isMoving ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                               : PlayerAnimationSet::PAS_CROUCH_IDLE;
        return in.isMoving ? PlayerAnimationSet::PAS_WALK : PlayerAnimationSet::PAS_IDLE;
    }

    // First checks of every GROUNDED state: death, walking off a ledge, jumping.
    PlayerAnimationSet commonGround(const PlayerInput& in)
    {
        if (in.dead) return PlayerAnimationSet::PAS_DIE;

        if (!in.isGrounded) {
            if (in.isShooting) return airShoot(in, in.isMoving);
            return in.isMoving ? PlayerAnimationSet::PAS_FALLING_FORWARD
                               : PlayerAnimationSet::PAS_FALLING;
        }

        // Same condition as Player::handleMovement, otherwise we'd animate a
        // jump that never happens.
        if (in.isJumping && !(in.isCrouching && in.isShooting)) {
            if (in.isShooting) return airShoot(in, in.isMoving);
            return in.isMoving ? PlayerAnimationSet::PAS_JUMP_FORWARD
                               : PlayerAnimationSet::PAS_JUMP_UP;
        }

        return NO_CHANGE;
    }

    // First checks of every AIR state: death and landing.
    PlayerAnimationSet commonAir(const PlayerInput& in)
    {
        if (in.dead)       return PlayerAnimationSet::PAS_DIE;
        if (in.isGrounded) return landing(in);
        return NO_CHANGE;
    }
}

// --- Parachute ----------------------------------------------------------------
// Not grounded-driven on purpose: the parachute plays for a fixed time and
// Player::update enables the player when PARACHUTE_CLOSE ends.
PlayerAnimationSet ParachuteState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.onAnimationEnd) current = PlayerAnimationSet::PAS_PARACHUTE_CLOSE;

    return current;
}

PlayerAnimationSet ParachuteCloseState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.onAnimationEnd) current = PlayerAnimationSet::PAS_FALLING;

    return current;
}

// --- Idle -------------------------------------------------------------------
PlayerAnimationSet IdleState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)   return groundShoot(in);
    if (in.isCrouching)  return in.isMoving ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                            : PlayerAnimationSet::PAS_CROUCH_IDLE;
    if (in.isMoving)     return PlayerAnimationSet::PAS_WALK;
    return current;
}

// --- Walk -------------------------------------------------------------------
PlayerAnimationSet WalkState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)   return groundShoot(in);
    if (in.isCrouching)  return in.isMoving ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                            : PlayerAnimationSet::PAS_CROUCH_IDLE;
    if (!in.isMoving)    return PlayerAnimationSet::PAS_AFTER_RUN_STOP;
    return current;
}

// --- AfterRun -----------------------------------------------------------
PlayerAnimationSet AfterRunState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)   return groundShoot(in);
    if (in.isCrouching)  return in.isMoving ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                            : PlayerAnimationSet::PAS_CROUCH_IDLE;
    if (in.isMoving)     return PlayerAnimationSet::PAS_WALK;
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_IDLE;
    return current;
}

// --- Crouch / CrouchWalking -----------------------------------------------
PlayerAnimationSet CrouchState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    // commonGround lets crouch+shoot beat jump (handleMovement blocks that jump),
    // so the old "shoot + jump while crouched" lines were unreachable and are gone.
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)   return groundShoot(in);
    if (!in.isCrouching) return in.isMoving ? PlayerAnimationSet::PAS_WALK : PlayerAnimationSet::PAS_IDLE;
    if (in.isMoving)     return PlayerAnimationSet::PAS_CROUCH_WALKING;
    return current;
}

PlayerAnimationSet CrouchWalkingState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)   return groundShoot(in);
    if (!in.isCrouching) return in.isMoving ? PlayerAnimationSet::PAS_WALK : PlayerAnimationSet::PAS_IDLE;
    if (!in.isMoving)    return PlayerAnimationSet::PAS_CROUCH_IDLE;
    return current;
}

// --- JumpUp / JumpForward ---------------------------------------------------
// Shooting takes priority over the clip ending; landing takes priority over both.
PlayerAnimationSet JumpUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return airShoot(in, false);
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_FALLING;
    return current;
}

PlayerAnimationSet JumpForwardState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    // W + shoot used to go to SHOOTING_JUMP_UP (aims forward) while the bullet
    // flies up; airShoot picks the up-aim clip.
    if (in.isShooting)     return airShoot(in, true);
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_FALLING_FORWARD;
    return current;
}

// --- Falling / FallingForward -----------------------------------------------
// No onAnimationEnd here: falling has no fixed-length clip to wait out,
// isGrounded alone decides when you leave it.
PlayerAnimationSet FallingState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting) return airShoot(in, false);
    return current;
}

PlayerAnimationSet FallingForwardState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting) return airShoot(in, true);
    return current;
}

// --- Shooting idle/walk variants ---------------------------------------------
// A shot restarts the clip (Player::update passes reset=true), so groundShoot
// can safely return the state we are already in.
PlayerAnimationSet ShootingIdleState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return groundShoot(in);
    if (in.isCrouching)    return in.isMoving ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                              : PlayerAnimationSet::PAS_CROUCH_IDLE;
    if (in.isMoving)       return PlayerAnimationSet::PAS_WALK;
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_IDLE;
    return current;
}

// Aim-up wins over crouch (Player::update aims the gun up whenever W is held), so
// W + S + shoot stands up and plays the up clip. S must NOT be checked mid-clip:
// it is still held, so checking it dropped back to CROUCH_IDLE one tick later and
// you shot up while looking crouched. S only decides where we go once the clip is
// over (or when you start moving, which cancels it like every other shoot clip).
PlayerAnimationSet ShootingIdleUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return groundShoot(in);
    if (in.isMoving)       return in.isCrouching ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                                 : PlayerAnimationSet::PAS_WALK;
    if (in.onAnimationEnd) return in.isCrouching ? PlayerAnimationSet::PAS_CROUCH_IDLE
                                                 : PlayerAnimationSet::PAS_IDLE;
    return current;
}

PlayerAnimationSet ShootingWalkState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return groundShoot(in);
    if (in.isCrouching)    return in.isMoving ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                              : PlayerAnimationSet::PAS_CROUCH_IDLE;
    if (!in.isMoving)      return PlayerAnimationSet::PAS_AFTER_RUN_STOP;
    // we are still moving here, so the clip ending means back to WALK
    // (it used to return IDLE, which flashed one frame of idle every time)
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_WALK;
    return current;
}

PlayerAnimationSet ShootingWalkUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    // groundShoot first: the old "!isMoving && shooting && inputUp" line sat
    // below a plain "!isMoving" and could never run.
    if (in.isShooting)     return groundShoot(in);
    // Same rule as ShootingIdleUp: S is not checked while the aim-up clip plays
    // (W + S + shoot while crouch-walking must stay in the up pose), only when we
    // stop moving or the clip ends.
    if (!in.isMoving)      return in.isCrouching ? PlayerAnimationSet::PAS_CROUCH_IDLE
                                                 : PlayerAnimationSet::PAS_AFTER_RUN_STOP;
    // The old "!inputUp -> SHOOTING_WALK" replayed a forward shot clip with no
    // shot fired. Like ShootingIdleUp, only a new shot changes the pose.
    if (in.onAnimationEnd) return in.isCrouching ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                                 : PlayerAnimationSet::PAS_WALK;
    return current;
}

// While this clip plays with S held, Player::handleMovement locks horizontal
// movement, so we must leave it as soon as S is released (otherwise you slide
// around with the crouch-shoot sprite until the clip ends).
PlayerAnimationSet ShootingCrouchState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return groundShoot(in);
    if (!in.isCrouching)   return in.isMoving ? PlayerAnimationSet::PAS_WALK : PlayerAnimationSet::PAS_IDLE;
    if (in.onAnimationEnd) return in.isMoving ? PlayerAnimationSet::PAS_CROUCH_WALKING
                                              : PlayerAnimationSet::PAS_CROUCH_IDLE;
    return current;
}

// --- ShootingJumpUp / ShootingUpJumpUp / ShootingJumpForward / ShootingJumpDown
// All four follow the same shape: landing, new shot (airShoot picks the aim),
// clip end -> falling. Previously only ShootingJumpUp could switch to the
// down-aim clip, ShootingUpJumpUp could not drop back to forward aim, and
// ShootingJumpForward had no landing check at all.
PlayerAnimationSet ShootingJumpUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return airShoot(in, false);
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_FALLING;
    return current;
}

PlayerAnimationSet ShootingUpJumpUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return airShoot(in, false);
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_FALLING;
    return current;
}

PlayerAnimationSet ShootingJumpForwardState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return airShoot(in, true);
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_FALLING_FORWARD;
    return current;
}

PlayerAnimationSet ShootingJumpDownState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonAir(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return airShoot(in, in.isMoving);
    if (in.onAnimationEnd) return in.isMoving ? PlayerAnimationSet::PAS_FALLING_FORWARD
                                              : PlayerAnimationSet::PAS_FALLING;
    return current;
}

// --- Melee ------------------------------------------------------------------
// The melee swing is committed: moving does not cancel it, only a jump / ledge
// (commonGround), a new shot, or the clip ending does.
PlayerAnimationSet MeleeAttackStateIdle::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return groundShoot(in);   // melee again, or a bullet if the enemy is gone
    if (in.onAnimationEnd) return landing(in);
    return current;
}

PlayerAnimationSet MeleeAttackStateWalk::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    const PlayerAnimationSet common = commonGround(in);
    if (common != NO_CHANGE) return common;

    if (in.isShooting)     return groundShoot(in);
    if (in.onAnimationEnd) return landing(in);
    return current;
}

// --- Death chain ------------------------------------------------------------
PlayerAnimationSet DeadState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{

    if (in.onAnimationEnd)
    {
        return PlayerAnimationSet::PAS_DIE_STILL;
    }
    return current;
}

PlayerAnimationSet DeadStillState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{

    if (in.onAnimationEnd)
    {
        return PlayerAnimationSet::PAS_REVIVE;
    }
    return current;
}

PlayerAnimationSet ReviveState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.onAnimationEnd)
    {
        return PlayerAnimationSet::PAS_IDLE;
    }
    return current;
}

// --- Static instances + lookup table -----------------------------------

namespace
{
    ParachuteState           parachuteInstance;
    ParachuteCloseState      parachuteCloseInstance;
    IdleState                idleInstance;
    WalkState                walkInstance;
    AfterRunState            afterRunInstance;
    CrouchState              crouchInstance;
    CrouchWalkingState       crouchWalkingInstance;
    JumpUpState              jumpUpInstance;
    JumpForwardState         jumpForwardInstance;
    FallingState             fallingInstance;
    FallingForwardState      fallingForwardInstance;
    ShootingIdleState        shootingIdleInstance;
    ShootingIdleUpState      shootingIdleUpInstance;
    ShootingWalkState        shootingWalkInstance;
    ShootingWalkUpState      shootingWalkUpInstance;
    ShootingCrouchState      shootingCrouchInstance;
    ShootingJumpUpState      shootingJumpUpInstance;
    ShootingUpJumpUpState    shootingUpJumpUpInstance;
    ShootingJumpForwardState shootingJumpForwardInstance;
    ShootingJumpDownState    shootingJumpDownInstance;
    MeleeAttackStateIdle     meleeAttackIdleInstance;
    MeleeAttackStateWalk     meleeAttackWalkInstance;
    DeadState                deadInstance;
    DeadStillState           deadStillInstance;
    ReviveState              reviveInstance;
}

// Order MUST match PlayerAnimationSet.
PlayerState* getPlayerState(PlayerAnimationSet index)
{
    static PlayerState* table[PlayerAnimationSet::PAS_COUNTS] =
    {
        &parachuteInstance,             // PAS_PARACHUTE
        &parachuteCloseInstance,        // PAS_PARACHUTE_CLOSE
        &idleInstance,                  // PAS_IDLE
        &walkInstance,                  // PAS_WALK
        &afterRunInstance,              // PAS_AFTER_RUN_STOP
        &crouchInstance,                // PAS_CROUCH_IDLE
        &crouchWalkingInstance,         // PAS_CROUCH_WALKING
        &jumpUpInstance,                // PAS_JUMP_UP
        &jumpForwardInstance,           // PAS_JUMP_FORWARD
        &fallingInstance,               // PAS_FALLING
        &fallingForwardInstance,        // PAS_FALLING_FORWARD
        &shootingIdleInstance,          // PAS_SHOOTING_IDLE
        &shootingIdleUpInstance,        // PAS_SHOOTING_IDLE_UP
        &shootingWalkInstance,          // PAS_SHOOTING_WALK
        &shootingWalkUpInstance,        // PAS_SHOOTING_WALK_UP
        &shootingCrouchInstance,        // PAS_SHOOTING_CROUCH
        &shootingJumpUpInstance,        // PAS_SHOOTING_JUMP_UP
        &shootingUpJumpUpInstance,      // PAS_SHOOTING_UP_JUMP_UP
        &shootingJumpForwardInstance,   // PAS_SHOOTING_JUMP_FORWARD
        &shootingJumpDownInstance,      // PAS_SHOOTING_JUMP_DOWN
        &meleeAttackIdleInstance,       // PAS_MELEE_ATTACK_IDLE
        &meleeAttackWalkInstance,       // PAS_MELEE_ATTACK_WALK
        &deadInstance,                  // PAS_DIE
        &deadStillInstance,             // PAS_DIE_STILL
        &reviveInstance                 // PAS_REVIVE
    };
    return table[index];
}