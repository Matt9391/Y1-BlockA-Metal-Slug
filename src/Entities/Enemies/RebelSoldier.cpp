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

	getAnimationSets()[EnemyAnimationSet::EAS_JUMP] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_JUMP_UP,
			ResourceIDFrames::IDF_REBELSOLDIER_JUMP_UP,
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

}

void RebelSoldier::update(float dt) {
	getAnimator().playAnimation(dt);

	EnemyAnimationSet nextState = state->update(*this, dt, static_cast<EnemyAnimationSet>(getCurrentASIndex()));
	if (nextState != getCurrentASIndex()) {
		setCurrentASIndex(nextState);
		state = RebelSoldierStates::getEnemyState(static_cast<EnemyAnimationSet>(getCurrentASIndex()));
		state->enter(*this);

	}


	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], getFlip());

	//const bool isGrounded = getRigidBody()->isGrounded();
	//getRigidBody()->setVelocityX(0.1f * getDir().x);

	//if (!isGrounded) {
	//	getRigidBody()->addVelocity(vec2(0, 0.001f * dt));
	//}
	//else {
	//	getRigidBody()->setVelocityY(0);
	//}


	this->addToPos(getRigidBody()->getVelocity() * dt);

}

