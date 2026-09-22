#include "precomp.h"
#include "Enemy.h"
#include <RigidBody.h>

Enemy::Enemy(vec2 pos) :
	Entity(pos, true),
	flip(false),
	sensors{}
{
	
}

void Enemy::setFlip(bool flip) {
	this->flip = flip;
}
bool Enemy::getFlip() const {
	return this->flip;
}

void Enemy::loadSensors(vec2 playerPos) {
	//struct EnemySensor {
	//	float distToPlayer;
	//	bool allyDiedNearby;
	//	bool wallAhead;
	//	bool platformAbove;
	//};

	this->sensors = {
		this->getPos().x - playerPos.x,
		false,
		false,
		false,
		getRigidBody()->isGrounded(),
		getAnimator().isAnimationEnded()
	};
}

const EnemySensor& Enemy::getSensors() const {
	return this->sensors;
}
