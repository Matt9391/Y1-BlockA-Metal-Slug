#include "precomp.h"
#include "EnemyState.h"
#include <Enemy.h>
#include <EnemyAnimationSet.h>


namespace EnemyStates{

void IdleState::enter(Enemy& e) {
    this->duration = RandomFloat() * 800.f + 400.f;
    this->elapsedTime = 0.f;
}

EnemyAnimationSet IdleState::update(Enemy& e, float dt, EnemyAnimationSet current)
{
    elapsedTime += dt;
    if (RandomFloat() * 100 > 0.05f) {
        e.setFlip(!e.getFlip());
    }
    
    if (elapsedTime > duration || e.getSensors().playerVisible) {
        current = EnemyAnimationSet::EAS_WALK;
    }

	return current;
}

EnemyAnimationSet WalkState::update(Enemy& e, float dt, EnemyAnimationSet current) 
{
    //if (e.getVelocity().x < 0.0001f) {
    //    current = EnemyAnimationSet::EAS_IDLE;
    //}
    return current;
}

EnemyAnimationSet AfterRunState::update(Enemy& e, float dt, EnemyAnimationSet current) 
{
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
        &EnemyStates::idleInstance,                // PAS_IDLE
        &EnemyStates::walkInstance,                // PAS_WALK
        &EnemyStates::afterRunInstance            // PAS_AFTER_RUN_STOP
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