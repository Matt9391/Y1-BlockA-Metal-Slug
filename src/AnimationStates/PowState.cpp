#include "precomp.h"
#include "PowState.h"
#include <PowAnimationSet.h>
#include <Pow.h>

namespace PowStates {

	void IdleState::enter(Pow& pow) {
		pow.setDir(vec2(0, 0));
	}

	PowAnimationSet IdleState::update(Pow& pow, float dt, PowAnimationSet current) {
		if (pow.isReleased()) {
			current = PowAnimationSet::POW_RELEASING;
		}
		return current;
	}

	void ReleasingState::enter(Pow& pow) {
		pow.setDir(vec2(0, 0));
	}

	PowAnimationSet ReleasingState::update(Pow& pow, float dt, PowAnimationSet current) {
		if (pow.isAnimationEnded()) {
			current = PowAnimationSet::POW_WALK_WAIT;
		}
		return current;
	}

	const float WalkWaitState::TRIGGERMINTIME = 1500.f;
	const int WalkWaitState::FLIPMS = 600.f;

	void WalkWaitState::enter(Pow& pow) {
		this->elapsedTime = 0.f;
		this->flipElapsedTime = 0.f;
		pow.setDir(vec2(-1, 0));
	}

	PowAnimationSet WalkWaitState::update(Pow& pow, float dt, PowAnimationSet current) {
		elapsedTime += dt;
		flipElapsedTime += dt;
		if (elapsedTime > TRIGGERMINTIME) {
			if (pow.isIntersectingPlayer())
				current = PowAnimationSet::POW_PANTS;;
		}

		if (flipElapsedTime > FLIPMS) {
			flipElapsedTime = 0.f;
			pow.setDir(vec2(pow.getDir().x * -1, 0));
		}

		return current;
	}

	void PantsState::enter(Pow& pow) {
		pow.setDir(vec2(0, 0));
	}

	PowAnimationSet PantsState::update(Pow& pow, float dt, PowAnimationSet current) {
		if (pow.isAnimationEnded()) {
			current = PowAnimationSet::POW_BYE;
		}
		return current;
	}

	void ByeState::enter(Pow& pow) {
		pow.setDir(vec2(0, 0));
	}

	PowAnimationSet ByeState::update(Pow& pow, float dt, PowAnimationSet current) {
		if (pow.isAnimationEnded()) {
			current = PowAnimationSet::POW_RUN_AWAY;
		}
		return current;
	}

	void RunAwayState::enter(Pow& pow) {
	
	}

	PowAnimationSet RunAwayState::update(Pow& pow, float dt, PowAnimationSet current) {
		pow.setDir(vec2(-1.f, 0));
		return current;
	}


    // --- Static instances + lookup table -----------------------------------
    IdleState                idleInstance;
    ReleasingState           releasingInstance;
    WalkWaitState            walkWaitInstance;
    PantsState               pantsInstance;
    ByeState                 byeInstance;
    RunAwayState             runAwayInstance;


    PowState* getPowState(PowAnimationSet index)
    {
        static PowState* table[PowAnimationSet::POW_COUNTS] =

        {
            &PowStates::idleInstance,         
            &PowStates::releasingInstance,    
            &PowStates::walkWaitInstance,     
            &PowStates::pantsInstance,        
            &PowStates::byeInstance,          
            &PowStates::runAwayInstance
        };
        return table[index];
    }


}