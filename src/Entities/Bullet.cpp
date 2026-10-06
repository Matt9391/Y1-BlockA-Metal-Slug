#include "precomp.h"
#include "Bullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

// TODO: divide bullet in subclasses
Bullet::Bullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed) :
	Entity(pos,needsRigidBody, EntityType::ET_BULLET),
	ableMovement(true),
	isDisabled(false),
	bulletType(bulletType)
{ 
	setDir(dir);
	switch (bulletType)
	{
		case BulletType::BT_PISTOL:
			setCollider(vec2(5, 5), vec2(0, 0));
			break;
		case BulletType::BT_FLAME_THROWER:
			setCollider(vec2(50, 30), vec2(0, 0));
			// setDir(vec2(getDir().x, getDir().y -0.1f));
			break;
	}

	getAnimationSets() = new AnimationSet[3];
	loadGFX();
	setCurrentASIndex(0);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], dir.x < 0);
	getRigidBody()->setSpeed(bulletSpeed);
}

Bullet::~Bullet() {
	delete[] getAnimationSets();
}

void Bullet::loadGFX() {
	
	switch (bulletType)
	{
		case BulletType::BT_PISTOL:
			getAnimationSets()[0] = AnimationSet(
			1,
			AnimationLayer(ResourceID::ID_PLAYER_BULLET_PISTOL,
				ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL,
				100,
				vec2(0, 0),
				vec2(0, 0))
			);
			
			getAnimationSets()[1] = AnimationSet(
				1,
				AnimationLayer(ResourceID::ID_PLAYER_BULLET_PISTOL_BOOM,
					ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL_BOOM,
					50,
					vec2(0, 0),
					vec2(0, 0))
			);
		break;
		case BulletType::BT_FLAME_THROWER:
			getAnimationSets()[0] = AnimationSet(
			1,
			AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER,
				ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER,
			40,
				vec2(0, -10),
				vec2(0, -10))
			);
			
			getAnimationSets()[1] = AnimationSet(
				1,
				AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM,
					ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM,
					50,
					vec2(0, -10),
					vec2(0, -10))
			);
			getAnimationSets()[2] = AnimationSet(
				1,
				AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM_STILL,
					ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM_STILL,
					70,
					vec2(0, -10),
					vec2(0, -10))
			);
		break;
	
		default:
		break;
	}

	
}

void Bullet::update(float dt) {
	getAnimator().playAnimation(dt);

	// DONE: should bounce again walls instead of ingoring them
	if (bulletType == BulletType::BT_FLAME_THROWER && getAnimator().isAnimationEnded() && getCurrentASIndex() == 0) {
		explode();
	}

	if (getAnimator().isAnimationEnded() && (getCurrentASIndex() == 1 || getCurrentASIndex() == 2)) {
		setFree(true);
	}

	if (!ableMovement) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void Bullet::explodeMap(){
	switch (bulletType)
	{
		case BulletType::BT_PISTOL:
			explode();
			break;
		case BulletType::BT_FLAME_THROWER:
			isDisabled = true;
			setDir(vec2(-0.01f, 0.f));
			setCurrentASIndex(2);
			getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
		break;
	}
}

void Bullet::explode() {
	switch (bulletType)
	{
		case BulletType::BT_PISTOL:
			setCurrentASIndex(1);
			getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
			ableMovement = false;
			isDisabled = true;
			break;
		case BulletType::BT_FLAME_THROWER:
			setCurrentASIndex(1);
			getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
		break;
	}
}

bool Bullet::getDisabled() const {
	return this->isDisabled;
}