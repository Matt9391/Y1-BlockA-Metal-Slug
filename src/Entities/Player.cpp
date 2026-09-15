#include "precomp.h"
#include "Player.h"
#include <vec2.h>
#include <iostream>
#include <ResourceManager.h>
#include <PlayerAnimationSet.h>
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <InputManager.h>

	
Player::Player(vec2 pos, InputManager& inputManager) :
	Entity(pos, true),
	inputManager(inputManager)

	{
		getAnimationSets() = new AnimationSet[PlayerAnimationSet::PAS_COUNTS];
	}

Player::~Player() {
	delete[] getAnimationSets();
}

void Player::loadGFX() {
	getAnimationSets()[PlayerAnimationSet::PAS_IDLE] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS,
			ResourceIDFrames::IDF_PLAYER_IDLE_LEGS,
			100,
			vec2(2, 9),
			vec2(-23, 9)),
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_BODY,
			ResourceIDFrames::IDF_PLAYER_IDLE_BODY,
			200,
			vec2(0, 0),
			vec2(-22, 0))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_WALK] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_WALK_LEGS,
			ResourceIDFrames::IDF_PLAYER_WALK_LEGS,
			100,
			vec2(0, 19),
			vec2(-22, 19)),
		AnimationLayer(ResourceID::ID_PLAYER_WALK_BODY,
			ResourceIDFrames::IDF_PLAYER_WALK_BODY,
			90,
			vec2(2, -2),
			vec2(-25, -2))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_AFTER_RUN_STOP] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_AFTER_RUN_STOP_F,
			ResourceIDFrames::IDF_PLAYER_AFTER_RUN_STOP_F,
			150,
			vec2(3, 1),
			vec2(-25, 1))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_JUMPUP] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS,
			80,
			vec2(7, 20),
			vec2(-23, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_BODY,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_BODY,
			80,
			vec2(0, -3),
			vec2(-25, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_FALLING] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_FALLING_LEGS,
			ResourceIDFrames::IDF_PLAYER_FALLING_LEGS,
			100,
			vec2(7, 20),
			vec2(-23, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_FALLING_BODY,
			ResourceIDFrames::IDF_PLAYER_FALLING_BODY,
			100,
			vec2(0, -3),
			vec2(-25, -3))
	);

	//getAnimator().setAnimation(&getAnimationSets()[PlayerAnimationSet::PAS_AFTER_RUN_STOP]);
	setCurrentASIndex(PlayerAnimationSet::PAS_IDLE);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
}

void Player::update(float dt) {
	getAnimator().playAnimation(dt);

	setLastDir(getDir());

	const bool inputRight = inputManager.isKeyPressed('D');
	const bool inputLeft = inputManager.isKeyPressed('A');
	const bool isMoving = inputRight || inputLeft;
	const bool isJumping = inputManager.isKeyPressed(' ');

	if (inputRight) {
		setDir(vec2(1, 0));
		addToPos(vec2(0.5f * dt, 0));
	}
	else if (inputLeft) {
		setDir(vec2(-1, 0));
		addToPos(vec2(-0.5f * dt, 0));
	}

	if (isMoving) {
		if (isJumping) {
			setCurrentASIndex(PlayerAnimationSet::PAS_JUMPUP);
		}
		else {
			setCurrentASIndex(PlayerAnimationSet::PAS_WALK);
		}
	}
	else if (isJumping) {
		setCurrentASIndex(PlayerAnimationSet::PAS_JUMPUP);
	}
	else if (getCurrentASIndex() == PlayerAnimationSet::PAS_WALK) {
		setCurrentASIndex(PlayerAnimationSet::PAS_AFTER_RUN_STOP);
	}
	else if (getCurrentASIndex() == PlayerAnimationSet::PAS_AFTER_RUN_STOP && getAnimator().isAnimationEnded()) {
		setCurrentASIndex(PlayerAnimationSet::PAS_IDLE);
	}

	const bool flip = getDir().x < 0;
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()],flip);



}

