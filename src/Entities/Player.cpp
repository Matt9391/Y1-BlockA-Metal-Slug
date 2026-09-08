#include "precomp.h"
#include "Player.h"
#include <vec2.h>
#include <iostream>
#include <ResourceManager.h>

Player::Player(vec2 pos) :
	Entity(pos)
	{
	
	}

void Player::loadGFX(ResourceManager& resourceManager) {
	animationSets[0] = AnimationSet(
		2,
		AnimationLayer(resourceManager.getSprite(ResourceID::ID_PLAYER_IDLE_LEGS), ResourceID::ID_PLAYER_IDLE_LEGS, 1, 100, vec2(0, 7)),
		AnimationLayer(resourceManager.getSprite(ResourceID::ID_PLAYER_IDLE_BODY), ResourceID::ID_PLAYER_IDLE_BODY, 4, 100)
	);

	std::cout << resourceManager.getSprite(ResourceID::ID_PLAYER_IDLE_BODY) << std::endl;
	animator.setAnimation(&animationSets[0]);
}

void Player::update(float dt) {

}

void Player::display(float dt, Surface* screen) {
	screen->Clear(0xFF00ff00);
	//std::cout << bodySprite << std::endl;
	animator.playAnimation(dt, screen);
}