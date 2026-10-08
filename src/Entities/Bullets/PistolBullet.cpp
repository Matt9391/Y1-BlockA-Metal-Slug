#include "precomp.h"
#include "PistolBullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

// TODO: use correct bullets sprite on tank spritesheet 
PistolBullet::PistolBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed) :
    Bullet(pos,needsRigidBody,dir,bulletType,bulletSpeed)
{ 
	setDir(dir);
    setCollider(vec2(5, 5), vec2(0, 0));

	getAnimationSets() = new AnimationSet[BPistolAnimationSet::BP_COUNTS];
	loadGFX();
	setCurrentASIndex(BPistolAnimationSet::BP_SHOOT);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], dir.x < 0);
	getRigidBody()->setSpeed(bulletSpeed);
}

PistolBullet::~PistolBullet() {
	delete[] getAnimationSets();
}

void PistolBullet::loadGFX() {
	
    getAnimationSets()[BPistolAnimationSet::BP_SHOOT] = AnimationSet(
    1,
    AnimationLayer(ResourceID::ID_PLAYER_BULLET_PISTOL,
        ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL,
        100,
        vec2(0, 0),
        vec2(0, 0))
    );
    
    getAnimationSets()[BPistolAnimationSet::BP_BOOM] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_PISTOL_BOOM,
            ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL_BOOM,
            50,
            vec2(0, 0),
            vec2(0, 0))
			);

}

void PistolBullet::update(float dt) {
	getAnimator().playAnimation(dt);


	if (getAnimator().isAnimationEnded() && (getCurrentASIndex() == BPistolAnimationSet::BP_BOOM)) {
		setFree(true);
	}

	if (!getAbleMovement()) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void PistolBullet::explodeMap(){
    explode();
}

void PistolBullet::explode() {

    setCurrentASIndex(BPistolAnimationSet::BP_BOOM);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
    setAbleMovement(false);
    setDisabled(true);

}
