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
		animationSets = new AnimationSet[PlayerAnimationSet::PAS_COUNTS];
	}

Player::~Player() {
	delete[] animationSets;
}

void Player::loadGFX() {
	animationSets[PlayerAnimationSet::PAS_IDLE] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS, ResourceIDFrames::IDF_PLAYER_IDLE_LEGS, 100, vec2(0, 52)),
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_BODY, ResourceIDFrames::IDF_PLAYER_IDLE_BODY, 200)
	);

	animator.setAnimation(&animationSets[PlayerAnimationSet::PAS_IDLE]);
	this->currentASIndex = PlayerAnimationSet::PAS_IDLE;
}

void Player::update(float dt) {
	animator.playAnimation(dt);
}

void Player::display(float dt, Surface* screen) {
	
	//std::cout << bodySprite << std::endl;
	
}