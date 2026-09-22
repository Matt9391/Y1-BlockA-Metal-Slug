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
    bool playerVisible = abs(e.getSensors().distToPlayer) < VIEWRANGE;


    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
    }

    elapsedTime += dt;
    if (int(elapsedTime) % 300 == 0 && Rand(100) > MAXCHANCE - FLIPCHANCE) {
        e.setFlip(!e.getFlip());
    }

   
    
    if (elapsedTime > duration  || playerVisible) {
        current = EnemyAnimationSet::EAS_WALK;
    }
    if (!playerVisible && e.getSensors().allyDiedNearby) {
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
    bool playerVisible = abs(e.getSensors().distToPlayer) < VIEWRANGE;


    elapsedTime += dt;
    if (int(elapsedTime) % 300 == 0 && Rand(100) > MAXCHANCE - FLIPCHANCE) {
        e.setFlip(!e.getFlip());
        e.setDir(vec2(e.getFlip() ? 1 : -1, e.getDir().y));
    }
    
    

    e.setVelocityX(0.1f * e.getDir().x);

    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
        if (int(elapsedTime) % 350 == 0 && Rand(100) > MAXCHANCE - JUMPCHANCE) {
            e.addVelocity(vec2(0, -0.37f));
            e.setGrounded(false);
            current = EnemyAnimationSet::EAS_JUMP_FORWARD;
        }
    }

    if (elapsedTime > duration) {
        current = EnemyAnimationSet::EAS_STOP;
    }

    if (playerVisible && e.getSensors().wallAhead && elapsedTime > duration/3.f) {
        current = EnemyAnimationSet::EAS_COVER;
    }

    if (playerVisible && abs(e.getSensors().distToPlayer) < MELEERANGE) {
        current = EnemyAnimationSet::EAS_MELEE_ATTACK;
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

void JumpForwardState::enter(Enemy& e) {
    this->duration =  1000.f;
    this->elapsedTime = 0.f;
}

EnemyAnimationSet JumpForwardState::update(Enemy& e, float dt, EnemyAnimationSet current)
{
    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
        current = EnemyAnimationSet::EAS_IDLE;
    }

    if (e.getSensors().animationEnded) {
        current = EnemyAnimationSet::EAS_FALLING;
    }

	return current;
}
void ScaredState::enter(Enemy& e) {
    this->duration =  1000.f;
    this->elapsedTime = 0.f;
}

EnemyAnimationSet ScaredState::update(Enemy& e, float dt, EnemyAnimationSet current)
{
    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
        current = EnemyAnimationSet::EAS_IDLE;
    }

    if (e.getSensors().animationEnded) {
        current = EnemyAnimationSet::EAS_IDLE;
    }

	return current;
}

void FallingState::enter(Enemy& e) {
    this->duration =  1000.f;
    this->elapsedTime = 0.f;
}

EnemyAnimationSet FallingState::update(Enemy& e, float dt, EnemyAnimationSet current)
{
    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
        current = EnemyAnimationSet::EAS_IDLE;
    }

    if (e.getSensors().animationEnded) {
        current = EnemyAnimationSet::EAS_IDLE;
    }

	return current;
}

void CoverState::enter(Enemy& e) {
    this->duration = RandomFloat() * 1000.f + 1500.f;
    this->elapsedTime = 0.f;
}

EnemyAnimationSet CoverState::update(Enemy& e, float dt, EnemyAnimationSet current)
{
    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
    }

    bool playerVisible = abs(e.getSensors().distToPlayer) < VIEWRANGE;


    elapsedTime += dt;
    if (elapsedTime > duration) {
        current = EnemyAnimationSet::EAS_WALK;
        e.setFlip(!e.getFlip());
    }

    if (!playerVisible) {
        current = EnemyAnimationSet::EAS_IDLE;
    }

	return current;
}

void MeleeAttackState::enter(Enemy& e) {
    this->duration = 1000.f;
    this->elapsedTime = 0.f;
}

EnemyAnimationSet MeleeAttackState::update(Enemy& e, float dt, EnemyAnimationSet current)
{
    if (!e.getSensors().isGrounded) {
        e.addVelocity(vec2(0, 0.001f * dt));
    }
    else {
        e.setVelocityY(0.f);
    }

    bool playerVisible = abs(e.getSensors().distToPlayer) < VIEWRANGE;


    elapsedTime += dt;
    if (elapsedTime > MSTRIGGER) {
        e.setAttacking(true);
    }

    if (playerVisible && abs(e.getSensors().distToPlayer) > MELEERANGE && e.getSensors().animationEnded) {
        current = EnemyAnimationSet::EAS_WALK;
    }
    
    if (!playerVisible && e.getSensors().animationEnded) {
        current = EnemyAnimationSet::EAS_IDLE;
    }

    if (e.getSensors().animationEnded) {
        current = EnemyAnimationSet::EAS_WALK;
        e.setFlip(!e.getFlip());
    }

    if (current != EnemyAnimationSet::EAS_MELEE_ATTACK) {
        e.setAttacking(false);
    }

	return current;
}


// --- Static instances + lookup table -----------------------------------
    IdleState                idleInstance;
    WalkState                walkInstance;
    AfterRunState            afterRunInstance;
    JumpForwardState         jumpForwardInstance;
    ScaredState              scaredInstance;
    FallingState             fallingInstance;
    CoverState               coverInstance;
    MeleeAttackState         meleeAttackInstance;
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
        &RebelSoldierStates::afterRunInstance,            // PAS_AFTER_RUN_STOP
        &RebelSoldierStates::jumpForwardInstance,         // PAS_JUMP_FORWARD
        &RebelSoldierStates::scaredInstance,             // PAS_FALLING
        &RebelSoldierStates::fallingInstance,             // PAS_FALLING
        &RebelSoldierStates::coverInstance,               // PAS_COVER
        &RebelSoldierStates::meleeAttackInstance,         // PAS_MELEE_ATTACK
        //&crouchInstance,              // PAS_CROUCH_IDLE
        //&crouchWalkingInstance,       // PAS_CROUCH_WALKING
        //&jumpUpInstance,              // PAS_JUMP_UP
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