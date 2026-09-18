#pragma once
#include "PlayerAnimationSet.h"

class Player;

// Renamed from PlayerInputSnapshot. onAnimationEnd is now just another
// per-frame flag here instead of a separate virtual call — whatever drives
// your animation system sets it true for the one frame a clip finishes,
// exactly like isJumping/isShooting/etc. are set from input.
struct PlayerInput
{
    bool inputRight;
    bool inputLeft;
    bool isMoving;
    bool isJumping;
    bool isGrounded;
    bool isCrouching;
    bool isShooting;
    bool onAnimationEnd;
    int  dirY; // -1 = aiming up, 0 = neutral, 1 = aiming down
};

class PlayerState
{
public:
    virtual ~PlayerState() = default;
    virtual PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const = 0;
    virtual void enter(Player& player) const {}
};

// --- Ground / neutral states ---------------------------------------------

class IdleState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class WalkState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class AfterRunState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class CrouchState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class CrouchWalkingState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

// --- Airborne states --------------------------------------------------------

class JumpUpState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class JumpForwardState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class FallingState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class FallingForwardState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

// --- Shooting variants -------------------------------------------------------

class ShootingIdleState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class ShootingIdleUpState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class ShootingWalkState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class ShootingWalkUpState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class ShootingJumpUpState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class ShootingJumpForwardState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

class ShootingJumpDownState final : public PlayerState
{
public:
    PlayerAnimationSet handleInput(const PlayerInput& in, PlayerAnimationSet current) const override;
};

PlayerState* getPlayerState(PlayerAnimationSet index);