#include "precomp.h"
#include <Enemies/RebelSoldier.h>
#include <RigidBody.h>
#include <EnemyAnimationSet.h>
#include <EnemyState.h>
#include <Renderer.h>
#include <ResourceIDFrames.h>

RebelSoldier::RebelSoldier(vec2 pos) :
	Enemy(pos),
	state(nullptr),
	granades{},
	granadesCount(0)
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
	for (int i = 0; i < 10; i++) {
		delete granades[i];
	}
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

	getAnimationSets()[EnemyAnimationSet::EAS_GRANADE_ATTACK] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_GRANADE_ATTACK,
			ResourceIDFrames::IDF_REBELSOLDIER_GRANADE_ATTACK,
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

	for (int i = 0; i < 10; i++) {
		if (granades[i] == nullptr) continue;
		granades[i]->update(dt);
	}
}


bool RebelSoldier::throwGranade(vec2 dir) {
	int bIndex = -1;
	for (int i = 0; i < 10; i++) {
		if (granades[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;

	granades[bIndex] = new Granade(this->getPos(), false, dir);
	granadesCount++;

	return true;
}

void RebelSoldier::addRenderSets(Renderer& renderer) {
	for (int i = 0; i < 10; i++) {
		if (granades[i] == nullptr) continue;
		renderer.addRenderSet(granades[i]->getRenderSet());
	}
}

void RebelSoldier::freeGranade(int i) {
	if (granades[i]) {
		delete granades[i];
		granades[i] = nullptr;
		granadesCount--;
	}
}