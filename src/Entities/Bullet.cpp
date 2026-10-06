#include "precomp.h"
#include "Bullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

// DONE: divide bullet in subclasses
Bullet::Bullet(vec2 pos, bool needsRigidBody, vec2, BulletType bulletType, float bulletSpeed) :
	Entity(pos,needsRigidBody, EntityType::ET_BULLET),
	ableMovement(true),
	isDisabled(false),
	bulletType(bulletType)
{ 
	getRigidBody()->setSpeed(bulletSpeed);
}


bool Bullet::getDisabled() const {
	return this->isDisabled;
}

void Bullet::setDisabled(bool isDisabled_){
	this->isDisabled = isDisabled_;
}
void Bullet::setAbleMovement(bool ableMovement_){
	this->ableMovement = ableMovement_; 
}

bool Bullet::getAbleMovement() const{
	return this->ableMovement;
}