#include "precomp.h"
#include "Player.h"
#include <vec2.h>

Player::Player(vec2 pos) :
	Entity(pos)
	{
	}

void Player::update(float dt) {

}

void Player::display(Surface* screen) {
	screen->Clear(0xFF00ff00);
	
}