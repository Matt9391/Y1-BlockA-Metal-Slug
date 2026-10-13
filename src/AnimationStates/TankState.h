#pragma once

#include <TankAnimationSet.h>

namespace TankStates{

    // What the tank state machine needs to know to pick the next animation set
    struct TankInput
    {
        bool inputRight = false;
        bool inputLeft = false;
        bool isMoving = false;
        bool isGrounded = false;
        bool isShooting = false;
        bool onAnimationEnd = false;
        bool isHit = false;
        bool isDead = false;
    };

    class TankState
    {
        public:
        virtual ~TankState() = default;
        virtual TankAnimationSet handleInput(const TankInput& in, TankAnimationSet current) const = 0;
    };

    class TankIdleState final : public TankState
    {
        public:
        TankAnimationSet handleInput(const TankInput& in, TankAnimationSet current) const override;
    };

    class TankWalkState final : public TankState
    {
        public:
        TankAnimationSet handleInput(const TankInput& in, TankAnimationSet current) const override;
    };

    class TankShootState final : public TankState
    {
        public:
        TankAnimationSet handleInput(const TankInput& in, TankAnimationSet current) const override;
    };

    class TankHitState final : public TankState
    {
    public:
        TankAnimationSet handleInput(const TankInput& in, TankAnimationSet current) const override;
    };

    class TankExplosionState final : public TankState
    {
        public:
        TankAnimationSet handleInput(const TankInput& in, TankAnimationSet current) const override;
    };

    class TankExplosionStillState final : public TankState
    {
        public:
        TankAnimationSet handleInput(const TankInput& in, TankAnimationSet current) const override;
    };

    TankState* getTankState(TankAnimationSet index);
}