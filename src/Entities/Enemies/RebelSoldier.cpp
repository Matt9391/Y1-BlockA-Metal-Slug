#include "precomp.h"
#include <Enemies/RebelSoldier.h>
#include <RigidBody.h>
#include <EnemyAnimationSet.h>
#include <EnemyState.h>
#include <Renderer.h>
#include <ResourceIDFrames.h>

RebelSoldier::RebelSoldier(vec2 pos, const RebelSoldierData& rsData) :
	Enemy(pos, EntityType::ET_REBELSOLDIER),
	state(nullptr),
	granades{},
	granadesCount(0),
	rsData(rsData),
	deathTimeElapsed(0.f)
{
	setCollider(vec2(20, 37), vec2(3, 0));
	getAnimationSets() = new AnimationSet[EnemyAnimationSet::EAS_COUNTS];
	loadGFX();
	setCurrentASIndex(EnemyAnimationSet::EAS_IDLE);
	// The starting state's enter() sets up its (random) duration.
	state = RebelSoldierStates::getEnemyState(EnemyAnimationSet::EAS_IDLE); 
	state->enter(*this);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.1f);

}

RebelSoldier::~RebelSoldier() {
	delete[] getAnimationSets();
	for (int i = 0; i < MAXGRANADES; i++) {
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
	getAnimationSets()[EnemyAnimationSet::EAS_SCARED_RUN] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_SCARED_RUN,
			ResourceIDFrames::IDF_REBELSOLDIER_SCARED_RUN,
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
	
	getAnimationSets()[EnemyAnimationSet::EAS_DEATH] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_DEATH,
			ResourceIDFrames::IDF_REBELSOLDIER_DEATH,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
	
	getAnimationSets()[EnemyAnimationSet::EAS_DEATH_STILL] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_REBELSOLDIER_DEATH_STILL,
			ResourceIDFrames::IDF_REBELSOLDIER_DEATH_STILL,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

}

void RebelSoldier::update(float dt) {
	clearSounds();
	getAnimator().playAnimation(dt);
	setColliderSprite();

	// Dead soldiers no longer count for the player's melee check.
	if(!this->getAlive()){
		setPlayerCollisionEnabled(false);
	}

	// Gravity. The grounded flag comes from the sensors, filled after last frame's map collision.
	if (!getSensors().isGrounded) {
		addVelocity(vec2(0, getRigidBody()->getGravity() * dt));
	}
	else {
		setVelocityY(0.f);
	}

	// Corpse: remove it DEATHTIMER ms after the death clip is over.
	if (getCurrentASIndex() == EnemyAnimationSet::EAS_DEATH_STILL){
		deathTimeElapsed += dt;
		if(deathTimeElapsed > DEATHTIMER && getAnimator().isAnimationEnded()) {
			setFree(true);
		}
	}

	// Run the state machine; when it returns a different state, switch to it and call its enter().
	EnemyAnimationSet nextState = state->update(*this, dt, static_cast<EnemyAnimationSet>(getCurrentASIndex()));
	if (nextState != getCurrentASIndex()) {
		setCurrentASIndex(nextState);
		state = RebelSoldierStates::getEnemyState(static_cast<EnemyAnimationSet>(getCurrentASIndex()));
		state->enter(*this);

	}


	// Apply the animation of the (possibly new) state, mirrored when flip is true.
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], getFlip());

	// Move: horizontal speed from the direction the state chose, vertical from gravity / jumps.
	setVelocityX(getRigidBody()->getSpeed() * getDir().x);
	
	this->addToPos(getRigidBody()->getVelocity() * dt);

	// The soldier owns its grenades, so it updates them too.
	for (int i = 0; i < MAXGRANADES; i++) {
		if (granades[i] == nullptr) continue;
		granades[i]->update(dt);
	}
}


bool RebelSoldier::throwGranade(vec2 dir_) {
	int bIndex = -1;
	for (int i = 0; i < MAXGRANADES; i++) {
		if (granades[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;

	granades[bIndex] = new Granade(this->getPos(), false, dir_); // starts at the soldier's position, no RigidBody
	granadesCount++;

	return true;
}

void RebelSoldier::addRenderDatas(Renderer& renderer) {
	for (int i = 0; i < MAXGRANADES; i++) {
		if (granades[i] == nullptr) continue;
		renderer.addRenderData(granades[i]->getRenderData());
		
	}
}

int RebelSoldier::getMaxGranades() const {
	return MAXGRANADES;
}

const RebelSoldierData& RebelSoldier::getData() const {
	return rsData;
}

void RebelSoldier::freeGranade(int i) {
	if (granades[i]) {
		delete granades[i];
		granades[i] = nullptr;
		granadesCount--;
	}
}

Granade* RebelSoldier::getGranade(int i) const{
	if (granades[i]) return granades[i];
	
	return nullptr;
}