#include "precomp.h"
#include "Bullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>

Bullet::Bullet(vec2 pos, bool needsRigidBody, vec2 dir) :
	Entity(pos,needsRigidBody, EntityType::ET_BULLET),
	ableMovement(true),
	isDisabled(false)
{ 
	setCollider(vec2(5, 5), vec2(0, 0));
	getAnimationSets() = new AnimationSet[2];
	loadGFX();
	setCurrentASIndex(0);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	setDir(dir);
	getRigidBody()->setSpeed(0.5f);
}

Bullet::~Bullet() {
	delete[] getAnimationSets();
}

void Bullet::loadGFX() {
	getAnimationSets()[0] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_BULLET_PISTOL,
			ResourceIDFrames::IDF_BULLET_PISTOL,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
	
	getAnimationSets()[1] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_BULLET_PISTOL_BOOM,
			ResourceIDFrames::IDF_PLAYER_BULLLET_PISTOL_BOOM,
			50,
			vec2(0, 0),
			vec2(0, 0))
	);
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