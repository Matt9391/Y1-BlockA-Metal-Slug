#include "precomp.h"
#include "Pow.h"
#include <vec2.h>
#include <PowAnimationSet.h>
#include <ResourceIDFrames.h>
#include <PowState.h>
#include <RigidBody.h>

Pow::Pow(vec2 pos) :
	Entity(pos, true),
	state(nullptr),
	released(false),
	intersectingPlayer(false)
{
	setCollider(vec2(20, 37), vec2(3, 0));
	getAnimationSets() = new AnimationSet[PowAnimationSet::POW_COUNTS];
	loadGFX();
	setCurrentASIndex(PowAnimationSet::POW_IDLE);
	state = PowStates::getPowState(PowAnimationSet::POW_IDLE);
	state->enter(*this);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.05f);
}

Pow::~Pow() {
	delete[] getAnimationSets();
}


void Pow::loadGFX() {
	getAnimationSets()[PowAnimationSet::POW_IDLE] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_POW_IDLE,
			ResourceIDFrames::IDF_POW_IDLE,
			150,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[PowAnimationSet::POW_RELEASING] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_POW_RELEASING,
			ResourceIDFrames::IDF_POW_RELEASING,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[PowAnimationSet::POW_WALK_WAIT] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_POW_WALK_WAIT,
			ResourceIDFrames::IDF_POW_WALK_WAIT,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[PowAnimationSet::POW_PANTS] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_POW_PANTS,
			ResourceIDFrames::IDF_POW_PANTS,
			150,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[PowAnimationSet::POW_BYE] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_POW_BYE,
			ResourceIDFrames::IDF_POW_BYE,
			130,
			vec2(0, 0),
			vec2(0, 0))
	);

	getAnimationSets()[PowAnimationSet::POW_RUN_AWAY] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_POW_RUN_AWAY,
			ResourceIDFrames::IDF_POW_RUN_AWAY,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
}


void Pow::update(float dt) {
	getAnimator().playAnimation(dt);


	PowAnimationSet nextState = state->update(*this, dt, static_cast<PowAnimationSet>(getCurrentASIndex()));
	if (nextState != getCurrentASIndex()) {
		setCurrentASIndex(nextState);
		state = PowStates::getPowState(static_cast<PowAnimationSet>(getCurrentASIndex()));
		state->enter(*this);

	}

	RigidBody* rb = getRigidBody();

	rb->setVelocityX(rb->getSpeed() * getDir().x);

	if (!rb->isGrounded()) {
		rb->addVelocity(vec2(0, rb->getGravity() * dt));
	}
	else {
		rb->setVelocityY(0);
	}


	this->addToPos(rb->getVelocity() * dt);

	const bool flip = getDir().x == 0 ? getLastDir().x < 0 : getDir().x < 0;
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], !flip);
}

bool Pow::isReleased() const {
	return this->released;
}

void Pow::setReleased(bool released) {
	this->released = released;
}


bool Pow::isAnimationEnded() {
	return this->getAnimator().isAnimationEnded();
}

bool Pow::isIntersectingPlayer() const {
	return this->intersectingPlayer;
}
void Pow::setIntersectingPlayer(bool intersect) {
	this->intersectingPlayer = intersect;
}

