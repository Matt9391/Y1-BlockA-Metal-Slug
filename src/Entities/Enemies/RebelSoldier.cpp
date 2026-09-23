#include "precomp.h"
#include <Enemies/RebelSoldier.h>
#include <RigidBody.h>
#include <EnemyAnimationSet.h>
#include <EnemyState.h>
#include <ResourceIDFrames.h>

RebelSoldier::RebelSoldier(vec2 pos) :
	Enemy(pos),
	state(nullptr)
{
	setCollider(vec2(20, 37), vec2(3, 0));
	getAnimationSets() = new AnimationSet[EnemyAnimationSet::EAS_COUNTS];
	loadGFX();
	setCurrentASIndex(EnemyAnimationSet::EAS_IDLE);
	state = RebelSoldierStates::getEnemyState(EnemyAnimationSet::EAS_IDLE);
	state->enter(*this);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.1f);

}

RebelSoldier::~RebelSoldier() {
	delete[] getAnimationSets();
}

void RebelSoldier::loadGFX() {
	getAnimationSets()[EnemyAnimationSet::EAS_IDLE] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_IDLE,
			ResourceIDFrames::IDF_REBELSOLDIER_IDLE,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[EnemyAnimationSet::EAS_WALK] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_WALK,
			ResourceIDFrames::IDF_REBELSOLDIER_WALK,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[EnemyAnimationSet::EAS_STOP] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_STOP,
			ResourceIDFrames::IDF_REBELSOLDIER_STOP,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[EnemyAnimationSet::EAS_JUMP_FORWARD] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_JUMP_FORWARD,
			ResourceIDFrames::IDF_REBELSOLDIER_JUMP_FORWARD,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
	
	getAnimationSets()[EnemyAnimationSet::EAS_SCARED] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_SCARED,
			ResourceIDFrames::IDF_REBELSOLDIER_SCARED,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[EnemyAnimationSet::EAS_FALLING] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_FALLING,
			ResourceIDFrames::IDF_REBELSOLDIER_FALLING,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[EnemyAnimationSet::EAS_COVER] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_COVER,
			ResourceIDFrames::IDF_REBELSOLDIER_COVER,
			100,
			vec2(-2, -8),
			vec2(-2, -8))
	);
	
	getAnimationSets()[EnemyAnimationSet::EAS_MELEE_ATTACK] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_MELEE_ATTACK,
			ResourceIDFrames::IDF_REBELSOLDIER_MELEE_ATTACK,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

}

void RebelSoldier::update(float dt) {
	getAnimator().playAnimation(dt);


	if (!getSensors().isGrounded) {
		addVelocity(vec2(0, getRigidBody()->getGravity() * dt));
	}
	else {
		setVelocityY(0.f);
	}


	EnemyAnimationSet nextState = state->update(*this, dt, static_cast<EnemyAnimationSet>(getCurrentASIndex()));
	if (nextState != getCurrentASIndex()) {
		setCurrentASIndex(nextState);
		state = RebelSoldierStates::getEnemyState(static_cast<EnemyAnimationSet>(getCurrentASIndex()));
		state->enter(*this);

	}


	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], getFlip());


	this->addToPos(getRigidBody()->getVelocity() * dt);

}

