#include "precomp.h"
#include "Missle.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

Missle::Missle(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed) :
    Bullet(pos,needsRigidBody,dir,bulletType,bulletSpeed)
{ 
	setDir(dir);
    setCollider(vec2(10, 25), vec2(0, 0));
	getAnimationSets() = new AnimationSet[BMissleAnimationSet::BM_COUNTS];
	loadGFX();
	setCurrentASIndex(BMissleAnimationSet::BM_SHOOT);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	getRigidBody()->setSpeed(bulletSpeed);
}

Missle::~Missle() {
	delete[] getAnimationSets();
}

void Missle::loadGFX() {
	
    getAnimationSets()[BMissleAnimationSet::BM_SHOOT] = AnimationSet(
    1,
    AnimationLayer(ResourceID::ID_MISSLE,
        ResourceIDFrames::IDF_MISSLE,
        100,
        vec2(0, 0),
        vec2(0, 0))
    );
    
    getAnimationSets()[BMissleAnimationSet::BM_BOOM] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_MISSLE_BOOM,
            ResourceIDFrames::IDF_MISSLE_BOOM,
            30,
            vec2(0, -10),
            vec2(0, -10))
			);

}

void Missle::update(float dt) {
	getAnimator().playAnimation(dt);


	if (getAnimator().isAnimationEnded() && (getCurrentASIndex() == BMissleAnimationSet::BM_BOOM)) {
		setFree(true);
	}

	if (!getAbleMovement()) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void Missle::explodeMap(){
    explode();
}

void Missle::explode() {

    setCurrentASIndex(BMissleAnimationSet::BM_BOOM);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
    setAbleMovement(false);
    setDisabled(true);

}
