#include "BossState.h"
#include <Enemies/Boss.h> 
#include <BossAnimationSet.h> 

namespace BossStates {

    // ---------- AttackOneState ----------
    void AttackOneState::enter(Boss& b)
    {
    }

    BossAnimationSet AttackOneState::update(Boss& b, float dt, BossAnimationSet current)
    {
        return current;
    }

    // ---------- AttackTwoState ----------
    void AttackTwoState::enter(Boss& b)
    {
    }

    BossAnimationSet AttackTwoState::update(Boss& b, float dt, BossAnimationSet current)
    {
        return current;
    }

    // ---------- MoveUpState ----------
    void MoveUpState::enter(Boss& b)
    {
    }

    BossAnimationSet MoveUpState::update(Boss& b, float dt, BossAnimationSet current)
    {
        return current;
    }

    // ---------- MoveDownState ----------
    void MoveDownState::enter(Boss& b)
    {
    }

    BossAnimationSet MoveDownState::update(Boss& b, float dt, BossAnimationSet current)
    {
        return current;
    }

    // ---------- DeathState ----------
    void DeathState::enter(Boss& b)
    {
    }

    BossAnimationSet DeathState::update(Boss& b, float dt, BossAnimationSet current)
    {
        return current;
    }

    AttackOneState           attackOneInstance;
    AttackTwoState           attackTwoInstance;
    MoveUpState              moveUpInstance;
    MoveDownState            moveDownInstance;
    DeathState               deathInstance;
 
    BossState* getBossState(BossAnimationSet index)
    {
        static BossState* table[BossAnimationSet::BAS_COUNTS] =
        {
            &BossStates::attackOneInstance,     // BAS_ATTACK_ONE
            &BossStates::attackTwoInstance,     // BAS_ATTACK_TWO
            &BossStates::moveUpInstance,        // BAS_MOVE_UP
            &BossStates::moveDownInstance,      // BAS_MOVE_DOWN
            &BossStates::deathInstance          // BAS_DEATH
        };
        return table[index];
    }

}