#include "precomp.h"
#include "PlayerState.h"

// --- Idle -------------------------------------------------------------------
PlayerAnimationSet IdleState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isJumping)                   return PlayerAnimationSet::PAS_JUMP_UP;
    if (in.isMoving && in.isCrouching)  return PlayerAnimationSet::PAS_CROUCH_WALKING;
    if (in.isCrouching)                 return PlayerAnimationSet::PAS_CROUCH_IDLE;
    if (in.isMoving)                    return PlayerAnimationSet::PAS_WALK;
    if (in.isShooting && in.dirY == -1) return PlayerAnimationSet::PAS_SHOOTING_IDLE_UP;
    if (in.isShooting)                  return PlayerAnimationSet::PAS_SHOOTING_IDLE;
    return current;
}

// --- Walk -------------------------------------------------------------------
PlayerAnimationSet WalkState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{

    if (in.isJumping)                   return PlayerAnimationSet::PAS_JUMP_FORWARD;
    if (in.isCrouching)                 return PlayerAnimationSet::PAS_CROUCH_WALKING;
    if (!in.isMoving)                   return PlayerAnimationSet::PAS_AFTER_RUN_STOP;
    if (in.isShooting && in.dirY == -1) return PlayerAnimationSet::PAS_SHOOTING_WALK_UP;
    if (in.isShooting)                  return PlayerAnimationSet::PAS_SHOOTING_WALK;
    return current;
}

// --- AfterRun -----------------------------------------------------------
PlayerAnimationSet AfterRunState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isJumping)      return PlayerAnimationSet::PAS_JUMP_UP;
    if (in.isMoving)       return PlayerAnimationSet::PAS_WALK;
    if (in.onAnimationEnd) return PlayerAnimationSet::PAS_IDLE;
    return current;
}

// --- Crouch / CrouchWalking -----------------------------------------------
// No shooting variant here — never shown in any version of the diagram.
PlayerAnimationSet CrouchState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (!in.isCrouching) return in.isMoving ? PlayerAnimationSet::PAS_WALK : PlayerAnimationSet::PAS_IDLE;
    if (in.isMoving)     return PlayerAnimationSet::PAS_CROUCH_WALKING;
    if (in.isJumping)     return PlayerAnimationSet::PAS_JUMP_UP;
    return current;
}

PlayerAnimationSet CrouchWalkingState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (!in.isCrouching) return in.isMoving ? PlayerAnimationSet::PAS_WALK : PlayerAnimationSet::PAS_IDLE;
    if (!in.isMoving)    return PlayerAnimationSet::PAS_CROUCH_IDLE;
    if (in.isJumping)     return PlayerAnimationSet::PAS_JUMP_FORWARD;

    return current;
}

// --- JumpUp / JumpForward ---------------------------------------------------
// onAnimationEnd -> Falling/FallingForward is now the last check: shooting
// takes priority if you start firing the same frame the jump clip ends.
PlayerAnimationSet JumpUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isShooting && in.dirY == 1) return PlayerAnimationSet::PAS_SHOOTING_JUMP_DOWN;
    if (in.isShooting)                 return PlayerAnimationSet::PAS_SHOOTING_JUMP_UP;
    if (in.onAnimationEnd)             return PlayerAnimationSet::PAS_FALLING;
    return current;
}

PlayerAnimationSet JumpForwardState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isShooting && in.dirY == 1) return PlayerAnimationSet::PAS_SHOOTING_JUMP_DOWN;
    if (in.isShooting)                 return PlayerAnimationSet::PAS_SHOOTING_JUMP_FORWARD;
    if (in.onAnimationEnd)             return PlayerAnimationSet::PAS_FALLING_FORWARD;
    return current;
}

// --- Falling / FallingForward -----------------------------------------------
// No onAnimationEnd here — falling has no fixed-length clip to wait out,
// isGrounded alone decides when you leave it, same as before.
PlayerAnimationSet FallingState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isGrounded)                 return PlayerAnimationSet::PAS_IDLE;
    if (in.isShooting && in.dirY == 1) return PlayerAnimationSet::PAS_SHOOTING_JUMP_DOWN;
    if (in.isShooting)                 return PlayerAnimationSet::PAS_SHOOTING_JUMP_UP;
    return current;
}

PlayerAnimationSet FallingForwardState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isGrounded)                 return PlayerAnimationSet::PAS_IDLE;
    if (in.isShooting && in.dirY == 1) return PlayerAnimationSet::PAS_SHOOTING_JUMP_DOWN;
    if (in.isShooting)                 return PlayerAnimationSet::PAS_SHOOTING_JUMP_FORWARD;
    return current;
}

// --- Shooting idle/walk variants ---------------------------------------------
PlayerAnimationSet ShootingIdleState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isMoving)        return PlayerAnimationSet::PAS_SHOOTING_WALK;
    if (in.dirY == -1)      return PlayerAnimationSet::PAS_SHOOTING_IDLE_UP;
    if (in.onAnimationEnd)  return PlayerAnimationSet::PAS_IDLE;
    return current;
}

PlayerAnimationSet ShootingIdleUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.isMoving)        return PlayerAnimationSet::PAS_SHOOTING_WALK_UP;
    if (in.onAnimationEnd)  return PlayerAnimationSet::PAS_IDLE;
    return current;
}

PlayerAnimationSet ShootingWalkState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (!in.isMoving)  return PlayerAnimationSet::PAS_AFTER_RUN_STOP;
    if (in.dirY == -1) return PlayerAnimationSet::PAS_SHOOTING_WALK_UP;
    return current;
}

PlayerAnimationSet ShootingWalkUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (!in.isMoving)  return PlayerAnimationSet::PAS_AFTER_RUN_STOP;
    if (in.dirY != -1) return PlayerAnimationSet::PAS_SHOOTING_WALK;
    return current;
}

// --- ShootingJumpUp / ShootingJumpForward / ShootingJumpDown ----------------
PlayerAnimationSet ShootingJumpUpState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.onAnimationEnd) return in.isGrounded ? PlayerAnimationSet::PAS_IDLE : PlayerAnimationSet::PAS_FALLING;
    return current;
}

PlayerAnimationSet ShootingJumpForwardState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.onAnimationEnd) return in.isGrounded ? PlayerAnimationSet::PAS_IDLE : PlayerAnimationSet::PAS_FALLING_FORWARD;
    return current;
}

PlayerAnimationSet ShootingJumpDownState::handleInput(const PlayerInput& in, PlayerAnimationSet current) const
{
    if (in.onAnimationEnd)
    {
        if (in.isGrounded) return PlayerAnimationSet::PAS_IDLE;
        if (in.isMoving)   return PlayerAnimationSet::PAS_FALLING_FORWARD;
        return PlayerAnimationSet::PAS_FALLING;
    }
    return current;
}

// --- Static instances + lookup table -----------------------------------

namespace
{
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
    ShootingJumpUpState      shootingJumpUpInstance;
    ShootingJumpForwardState shootingJumpForwardInstance;
    ShootingJumpDownState    shootingJumpDownInstance;
}

PlayerState* getPlayerState(PlayerAnimationSet index)
{
    static PlayerState* table[PlayerAnimationSet::PAS_COUNTS] =
    {
        &idleInstance,                // PAS_IDLE
        &walkInstance,                // PAS_WALK
        &afterRunInstance,            // PAS_AFTER_RUN_STOP
        &crouchInstance,              // PAS_CROUCH_IDLE
        &crouchWalkingInstance,       // PAS_CROUCH_WALKING
        &jumpUpInstance,              // PAS_JUMP_UP
        &jumpForwardInstance,         // PAS_JUMP_FORWARD
        &fallingInstance,             // PAS_FALLING
        &fallingForwardInstance,      // PAS_FALLING_FORWARD
        &shootingIdleInstance,        // PAS_SHOOTING_IDLE
        &shootingIdleUpInstance,      // PAS_SHOOTING_IDLE_UP
        &shootingWalkInstance,        // PAS_SHOOTING_WALK
        &shootingWalkUpInstance,      // PAS_SHOOTING_WALK_UP
        &shootingJumpUpInstance,      // PAS_SHOOTING_JUMP_UP
        &shootingJumpForwardInstance, // PAS_SHOOTING_JUMP_FORWARD
        &shootingJumpDownInstance     // PAS_SHOOTING_JUMP_DOWN
    };
    return table[index];
}