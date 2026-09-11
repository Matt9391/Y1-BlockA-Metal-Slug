#include "precomp.h"
#include "Player.h"
#include <vec2.h>
#include <iostream>
#include <ResourceManager.h>
#include <PlayerAnimationSet.h>
#include <ResourceIDFrames.h>

Player::Player(vec2 pos) :
	Entity(pos)
	{
		getAnimationSets() = new AnimationSet[PlayerAnimationSet::PAS_COUNTS];
	}

Player::~Player() {
	delete[] getAnimationSets();
}

void Player::loadGFX() {
	getAnimationSets()[PlayerAnimationSet::PAS_IDLE] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS, ResourceIDFrames::IDF_PLAYER_IDLE_LEGS, 100, vec2(0, 52)),
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_BODY, ResourceIDFrames::IDF_PLAYER_IDLE_BODY, 200)
	);

	getAnimator().setAnimation(&getAnimationSets()[PlayerAnimationSet::PAS_IDLE]);
	setCurrentASIndex(PlayerAnimationSet::PAS_IDLE);
}

void Player::update(float dt) {
	getAnimator().playAnimation(dt);

	if (GetAsyncKeyState('D')) {
		getAnimator().setAnimation(&getAnimationSets()[PlayerAnimationSet::PAS_IDLE] /*flipped=false*/ /*reset=false*/);
		//this->addToPos(vec2(1 * dt, 0));
	}
	else if(GetAsyncKeyState('A')) {
		getAnimator().setAnimation(&getAnimationSets()[PlayerAnimationSet::PAS_IDLE], /*flipped=*/true /*reset=false*/);
		//this->addToPos(vec2(-1 * dt, 0));
	}
}

