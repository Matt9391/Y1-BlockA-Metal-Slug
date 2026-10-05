#include "precomp.h"
#include "Enemy.h"
#include <RigidBody.h>

Enemy::Enemy(vec2 pos, EntityType entityType) :
	Entity(pos, true, entityType),
	flip(false),
	sensors{},
	attacking(false),
	alive(true)
{
	sensors.alive = true;
	sensors.isGrounded = true;
}

void Enemy::setFlip(bool flip_) {
	this->flip = flip_;
}
bool Enemy::getFlip() const {
	return this->flip;
}

void Enemy::setAttacking(bool attacking_) {
	this->attacking = attacking_;
}
bool Enemy::getAttacking() const {
	return this->attacking;
}

void Enemy::loadSensors(vec2 playerPos, bool wallAhead) {
	//struct EnemySensor {
	//	float distToPlayer;
	//	bool allyDiedNearby;
	//	bool wallAhead;
	//	bool platformAbove;
	//};

	this->sensors = {
		this->getPos().x - playerPos.x,
		false,
		wallAhead,
		false,
		getRigidBody()->isGrounded(),
		getAnimator().isAnimationEnded(),
		getAlive()
	};
}

const EnemySensor& Enemy::getSensors() const {
	return this->sensors;
}

void Enemy::setAlive(bool alive_) {
	this->alive = alive_;
}

bool Enemy::getAlive() const {

	return this->alive;

}
