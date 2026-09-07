#include "precomp.h"
#include "Player.h"
#include <vec2.h>
#include <iostream>
#include <ResourceManager.h>

Player::Player(vec2 pos) :
	Entity(pos),
	bodySprite(nullptr)
	{
		
	}

void Player::getSprites(ResourceManager& resourceManager) {
	std::cout << resourceManager.getSprite(ResourceID::PLAYER_IDLE_BODY) << std::endl;
	bodySprite = resourceManager.getSprite(ResourceID::PLAYER_IDLE_BODY);
}

void Player::update(float dt) {

}

void Player::display(Surface* screen) {
	screen->Clear(0xFF00ff00);
	//std::cout << bodySprite << std::endl;
	bodySprite->Draw(screen, pos.x, pos.y);
}