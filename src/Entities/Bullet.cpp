#include "precomp.h"
#include "Bullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

Bullet::Bullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed) :
	Entity(pos,needsRigidBody, EntityType::ET_BULLET),
	ableMovement(true),
	isDisabled(false),
	bulletType(bulletType)
{ 
	setCollider(vec2(5, 5), vec2(0, 0));
	getAnimationSets() = new AnimationSet[2];
	loadGFX();
	setCurrentASIndex(0);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	setDir(dir);
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
				100,
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
		break;
	
		default:
		break;
	}

	
}

void Bullet::update(float dt) {
	getAnimator().playAnimation(dt);

	if (getAnimator().isAnimationEnded() && getCurrentASIndex() == 1) {
		setFree(true);
	}

	if (!ableMovement) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void Bullet::explode() {
	setCurrentASIndex(1);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	ableMovement = false;
	isDisabled = true;
}

bool Bullet::getDisabled() const {
	return this->isDisabled;
}