#include "precomp.h"
#include "Bullet.h"
#include <ResourceIDFrames.h>

Bullet::Bullet(vec2 pos, bool needsRigidBody) :
	Entity(pos,needsRigidBody)
{ 
	setCollider(vec2(5, 5), vec2(0, 0));
	getAnimationSets() = new AnimationSet[1];
	loadGFX();
	setCurrentASIndex(0);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
}

Bullet::~Bullet() {
	delete[] getAnimationSets();
	delete getRigidBody();
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

	this->addToPos(vec2(0.1 * dt, 0));
}