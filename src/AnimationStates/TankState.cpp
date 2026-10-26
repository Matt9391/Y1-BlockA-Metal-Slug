#include "precomp.h"
#include "TankState.h"

namespace TankStates{

    // --- Idle -------------------------------------------------------------------
    TankAnimationSet TankIdleState::handleInput(const TankInput& in, TankAnimationSet current) const
    {
        if (in.isDead)       return TankAnimationSet::TAS_EXPLOSION;
        if (in.isHit)      return TankAnimationSet::TAS_HIT;
        if (in.isShooting) return TankAnimationSet::TAS_SHOOT;
        if (in.isMoving)   return TankAnimationSet::TAS_WALK;
        return current;
    }

    // --- Walk -------------------------------------------------------------------
    TankAnimationSet TankWalkState::handleInput(const TankInput& in, TankAnimationSet current) const
    {
        if (in.isDead)       return TankAnimationSet::TAS_EXPLOSION;
        if (in.isHit)      return TankAnimationSet::TAS_HIT;
        if (in.isShooting) return TankAnimationSet::TAS_SHOOT;
        if (!in.isMoving)  return TankAnimationSet::TAS_IDLE;
        return current;
    }

    // --- Shoot ------------------------------------------------------------------
    // The shoot clip plays to the end unless the tank dies or gets hit; if the button
    // is still held when it ends, the tank keeps shooting, otherwise it goes back to
    // walk / idle.
    TankAnimationSet TankShootState::handleInput(const TankInput& in, TankAnimationSet current) const
    {
        if (in.isDead)  return TankAnimationSet::TAS_EXPLOSION;
        if (in.isHit) return TankAnimationSet::TAS_HIT;
        if (in.onAnimationEnd)
        {
            if (in.isShooting) return current;
            return in.isMoving ? TankAnimationSet::TAS_WALK : TankAnimationSet::TAS_IDLE;
        }
        return current;
    }

    // --- Hit --------------------------------------------------------------------
    // Plays the hit clip to the end, then returns to whatever the player is doing.
    TankAnimationSet TankHitState::handleInput(const TankInput& in, TankAnimationSet current) const
    {
        if (in.isDead) return TankAnimationSet::TAS_EXPLOSION;
        if (in.onAnimationEnd)
        {
            if (in.isShooting) return TankAnimationSet::TAS_SHOOT;
            if (in.isMoving)   return TankAnimationSet::TAS_WALK;
            return TankAnimationSet::TAS_IDLE;
        }
        return current;
    }

    // --- Explosion --------------------------------------------------------------
    TankAnimationSet TankExplosionState::handleInput(const TankInput& in, TankAnimationSet current) const
    {
        if (in.onAnimationEnd) return TankAnimationSet::TAS_EXPLOSION_STILL;
        return current;
    }

    TankAnimationSet TankExplosionStillState::handleInput(const TankInput&, TankAnimationSet current) const
    {
        return current;
    }

    // --- Static instances + lookup table -----------------------------------

    namespace
    {
        TankIdleState            idleInstance;
        TankWalkState            walkInstance;
        TankShootState           shootInstance;
        TankHitState             hitInstance;
        TankExplosionState       explosionInstance;
        TankExplosionStillState  explosionStillInstance;
    }

    TankState* getTankState(TankAnimationSet index)
    {
        static TankState* table[TankAnimationSet::TAS_COUNTS] =
        {
            &idleInstance,              // TAS_IDLE
            &walkInstance,              // TAS_WALK
            &shootInstance,             // TAS_SHOOT
            &hitInstance,               // TAS_HIT
            &explosionInstance,         // TAS_EXPLOSION
            &explosionStillInstance     // TAS_EXPLOSION_STILL
        };
        return table[index];
    }
}