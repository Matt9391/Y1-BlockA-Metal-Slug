#include "precomp.h"
#include "Enemy.h"

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
	//	bool playerVisible;
	//	float distToPlayer;
	//	bool allyDiedNearby;
	//	bool wallAhead;
	//	bool platformAbove;
	//};
	this->sensors = {
		abs(this->getPos().x - playerPos.x) < 150,
		abs(this->getPos().x - playerPos.x),
		false,
		false,
		false
	};
}

const EnemySensor& Enemy::getSensors() const {
	return this->sensors;
}
