#include "precomp.h"
#include "EnemyState.h"
#include <Enemy.h>
#include <EnemyAnimationSet.h>


namespace RebelSoldierStates{

void IdleState::enter(Enemy& e) {
    this->duration = RandomFloat() * 3000.f + 400.f;
    this->elapsedTime = 0.f;
    e.setVelocityX(0.f);
}

EnemyAnimationSet IdleState::update(Enemy& e, float dt, EnemyAnimationSet current)
{
    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
    }

    elapsedTime += dt;
    if (int(elapsedTime) % 300 == 0 && Rand(100) > 75) {
        e.setFlip(!e.getFlip());
    }
    
    if (elapsedTime > duration  /* ||e.getSensors().playerVisible*/) {
        current = EnemyAnimationSet::EAS_WALK;
    }
    if (!e.getSensors().playerVisible && e.getSensors().allyDiedNearby) {
        current = EnemyAnimationSet::EAS_SCARED;
    }

	return current;
}

void WalkState::enter(Enemy& e) {
    this->duration = RandomFloat() * 3000.f + 1500.f;
    this->elapsedTime = 0.f;
    e.setDir(vec2(e.getFlip() ? 1 : -1, 0));

}

EnemyAnimationSet WalkState::update(Enemy& e, float dt, EnemyAnimationSet current) 
{
    elapsedTime += dt;
    if (int(elapsedTime) % 300 == 0 && Rand(100) > 95) {
        e.setFlip(!e.getFlip());
        e.setDir(vec2(e.getFlip() ? 1 : -1, e.getDir().y));
    }
    
    printf("e.getVelocity().x: %.2f ground: %d\n", e.getVelocity().x, e.getSensors().isGrounded);
    e.setVelocityX(0.1f * e.getDir().x);

    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
        //if (e.getSensors().) {
            //getRigidBody()->addVelocity(vec2(0, -0.37f));
            //setGrounded(false);
        //}
    }

    if (elapsedTime > duration) {
        current = EnemyAnimationSet::EAS_STOP;
    }

    if (e.getSensors().playerVisible && e.getSensors().distToPlayer < ATTACKRANGE) {

    }

    return current;
}

void AfterRunState::enter(Enemy& e) {
    this->duration =  1000.f;
    this->elapsedTime = 0.f;
}

EnemyAnimationSet AfterRunState::update(Enemy& e, float dt, EnemyAnimationSet current) 
{
    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
    }

    if (e.getSensors().animationEnded) {
        current = EnemyAnimationSet::EAS_IDLE;
    }

	return current;
}


// --- Static instances + lookup table -----------------------------------
    IdleState                idleInstance;
    WalkState                walkInstance;
    AfterRunState            afterRunInstance;
    //CrouchState              crouchInstance;
    //CrouchWalkingState       crouchWalkingInstance;
    //JumpUpState              jumpUpInstance;
    //JumpForwardState         jumpForwardInstance;
    //FallingState             fallingInstance;
    //FallingForwardState      fallingForwardInstance;
    //ShootingIdleState        shootingIdleInstance;
    //ShootingIdleUpState      shootingIdleUpInstance;
    //ShootingWalkState        shootingWalkInstance;
    //ShootingWalkUpState      shootingWalkUpInstance;
    //ShootingCrouchState      shootingCrouchInstance;
    //ShootingJumpUpState      shootingJumpUpInstance;
    //ShootingUpJumpUpState    shootingUpJumpUpIstance;
    //ShootingJumpForwardState shootingJumpForwardInstance;
    //ShootingJumpDownState    shootingJumpDownInstance;


EnemyState* getEnemyState(EnemyAnimationSet index)
{
    static EnemyState* table[EnemyAnimationSet::EAS_COUNTS] =
    {
        &RebelSoldierStates::idleInstance,                // PAS_IDLE
        &RebelSoldierStates::walkInstance,                // PAS_WALK
        &RebelSoldierStates::afterRunInstance            // PAS_AFTER_RUN_STOP
        //&crouchInstance,              // PAS_CROUCH_IDLE
        //&crouchWalkingInstance,       // PAS_CROUCH_WALKING
        //&jumpUpInstance,              // PAS_JUMP_UP
        //&jumpForwardInstance,         // PAS_JUMP_FORWARD
        //&fallingInstance,             // PAS_FALLING
        //&fallingForwardInstance,      // PAS_FALLING_FORWARD
        //&shootingIdleInstance,        // PAS_SHOOTING_IDLE
        //&shootingIdleUpInstance,      // PAS_SHOOTING_IDLE_UP
        //&shootingWalkInstance,        // PAS_SHOOTING_WALK
        //&shootingWalkUpInstance,      // PAS_SHOOTING_WALK_UP
        //&shootingCrouchInstance,      // PAS_SHOOTING_CROUCH
        //&shootingJumpUpInstance,      // PAS_SHOOTING_JUMP_UP
        //&shootingUpJumpUpIstance,      // PAS_SHOOTING_UP_JUMP_UP
        //&shootingJumpForwardInstance, // PAS_SHOOTING_JUMP_FORWARD
        //&shootingJumpDownInstance     // PAS_SHOOTING_JUMP_DOWN
    };
    return table[index];
}

}