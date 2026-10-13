#include "precomp.h"
#include "BossState.h"
#include <Enemies/Boss.h> 
#include <BossAnimationSet.h> 
#include <RigidBody.h> 

namespace BossStates {

    // ---------- AttackOneHighState ----------
    void AttackOneHighState::enter(Boss& b)
    {
        this->elapsedTime = 0.f;
        this->shootCount = 1;
    }

    BossAnimationSet AttackOneHighState::update(Boss& b, float dt, BossAnimationSet current)
    {
        if(!b.getSensors().alive){
            return BossAnimationSet::BAS_DEATH;
        }
        elapsedTime += dt;

        if(elapsedTime > THIRDSHOOT && shootCount == 3){
            b.shootCannon();
            shootCount++;
        }else if(elapsedTime > SECONDSHOOT && shootCount == 2){
            b.shootCannon();   
            shootCount++;         
        }else if(elapsedTime > FIRSTSHOOT && shootCount == 1){
            b.shootCannon();
            shootCount++;
        }

        if(b.getSensors().animationEnded){
            return BossAnimationSet::BAS_MOVE_DOWN;
        }
        return current;
    }

    // ---------- AttackOneLowState ----------
    void AttackOneLowState::enter(Boss& b)
    {
        this->elapsedTime = 0.f;
        this->shootCount = 1;
    }

    BossAnimationSet AttackOneLowState::update(Boss& b, float dt, BossAnimationSet current)
    {
        if(!b.getSensors().alive){
            return BossAnimationSet::BAS_DEATH;
        }
        elapsedTime += dt;

        if(elapsedTime > THIRDSHOOT && shootCount == 3){
            b.shootCannon();
            shootCount++;
        }else if(elapsedTime > SECONDSHOOT && shootCount == 2){
            b.shootCannon();   
            shootCount++;         
        }else if(elapsedTime > FIRSTSHOOT && shootCount == 1){
            b.shootCannon();
            shootCount++;
        }
        if(b.getSensors().animationEnded){
            return BossAnimationSet::BAS_MOVE_UP;
        }

        return current;
    }

    // ---------- AttackTwoHighState ----------
    void AttackTwoHighState::enter(Boss& b)
    {
    }

    BossAnimationSet AttackTwoHighState::update(Boss& b, float dt, BossAnimationSet current)
    {
        if(b.getSensors().animationEnded){
            b.shootBeam();
            return BossAnimationSet::BAS_MOVE_DOWN;
        }
        return current;
    }

    // ---------- AttackTwoLowState ----------
    void AttackTwoLowState::enter(Boss& b)
    {
    }

    BossAnimationSet AttackTwoLowState::update(Boss& b, float dt, BossAnimationSet current)
    {
        if(!b.getSensors().alive){
            return BossAnimationSet::BAS_DEATH;
        }
        if(b.getSensors().animationEnded){
            b.shootLaserBall();
            return BossAnimationSet::BAS_MOVE_UP;
        }
        return current;
    }

    // ---------- MoveUpState ----------
    void MoveUpState::enter(Boss& b)
    {
    }

    BossAnimationSet MoveUpState::update(Boss& b, float dt, BossAnimationSet current)
    {
        if(!b.getSensors().alive){
            return BossAnimationSet::BAS_DEATH;
        }
        b.moveShootOffset(vec2(0, -1 * dt * b.getRigidBody()->getSpeed()));

        if(b.getSensors().animationEnded){
            if(b.getHP() < 50){
                return BossAnimationSet::BAS_ATTACK_TWO_HIGH;
            }
            return BossAnimationSet::BAS_ATTACK_ONE_HIGH;
        }
        return current;
    }

    // ---------- MoveDownState ----------
    void MoveDownState::enter(Boss& b)
    {
    }

    BossAnimationSet MoveDownState::update(Boss& b, float dt, BossAnimationSet current)
    {
        if(!b.getSensors().alive){
            return BossAnimationSet::BAS_DEATH;
        }
        b.moveShootOffset(vec2(0, 1 * dt * b.getRigidBody()->getSpeed()));

        if(b.getSensors().animationEnded){
            if(b.getHP() < 50){
                return BossAnimationSet::BAS_ATTACK_TWO_LOW;
            }
            return BossAnimationSet::BAS_ATTACK_ONE_LOW;
        }
        return current;
    }

    // ---------- DeathState ----------
    void DeathState::enter(Boss& b)
    {
    }

    BossAnimationSet DeathState::update(Boss& b, float dt, BossAnimationSet current)
    {   
        printf("anim running\n");
        if(b.getSensors().animationEnded){
            printf("anim ended\n");
            return BossAnimationSet::BAS_DEATH_STILL;
        }
        return current;
    }
    
    void DeathStillState::enter(Boss& b)
    {
    }

    BossAnimationSet DeathStillState::update(Boss& b, float dt, BossAnimationSet current)
    {
        return current;
    }

    // --- Static instances + lookup table -----------------------------------
    AttackOneHighState       attackOneHighInstance;
    AttackOneLowState        attackOneLowInstance;
    AttackTwoHighState       attackTwoHighInstance;
    AttackTwoLowState        attackTwoLowInstance;
    MoveUpState              moveUpInstance;
    MoveDownState            moveDownInstance;
    DeathState               deathInstance;
    DeathStillState          deathStillInstance;

    BossState* getBossState(BossAnimationSet index)
    {
        static BossState* table[BossAnimationSet::BAS_COUNTS] =
        {
            &BossStates::attackOneHighInstance,   // BAS_ATTACK_ONE_HIGH
            &BossStates::attackOneLowInstance,   // BAS_ATTACK_ONE_LOW
            &BossStates::attackTwoHighInstance,   // BAS_ATTACK_TWO_HIGH
            &BossStates::attackTwoLowInstance,   // BAS_ATTACK_TWO_LOW
            &BossStates::moveUpInstance,   // BAS_MOVE_UP
            &BossStates::moveDownInstance,   // BAS_MOVE_DOWN
            &BossStates::deathInstance,    // BAS_DEATH
            &BossStates::deathStillInstance    // BAS_DEATH_STILL
        };
        return table[index];
    }

}