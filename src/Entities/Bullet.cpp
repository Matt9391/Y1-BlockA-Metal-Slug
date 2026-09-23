#include "precomp.h"
#include "Bullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>

Bullet::Bullet(vec2 pos, bool needsRigidBody, vec2 dir) :
	Entity(pos,needsRigidBody)
{ 
	setCollider(vec2(5, 5), vec2(0, 0));
	getAnimationSets() = new AnimationSet[1];
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
}

void Bullet::update(float dt) {
	getAnimator().playAnimation(dt);

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());
}