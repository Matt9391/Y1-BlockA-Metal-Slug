#include "precomp.h"
#include "LaserBall.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

LaserBall::LaserBall(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed) :
    Bullet(pos,needsRigidBody,dir,bulletType,bulletSpeed)
{ 
	setDir(dir);
    setCollider(vec2(40, 15), vec2(0, 10));
	getAnimationSets() = new AnimationSet[BLaserBallAnimationSet::BLB_COUNTS];
	loadGFX();
	setCurrentASIndex(BLaserBallAnimationSet::BLB_SHOOT);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	getRigidBody()->setSpeed(bulletSpeed);
}

LaserBall::~LaserBall() {
	delete[] getAnimationSets();
}

void LaserBall::loadGFX() {
	
    getAnimationSets()[BLaserBallAnimationSet::BLB_SHOOT] = AnimationSet(
    1,
    AnimationLayer(ResourceID::ID_LASER_BALL,
        ResourceIDFrames::IDF_LASER_BALL,
        100,
        vec2(0, 0),
        vec2(0, 0))
    );
    
    getAnimationSets()[BLaserBallAnimationSet::BLB_BOOM] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_LASER_BALL,
            ResourceIDFrames::IDF_LASER_BALL,
            30,
            vec2(0, -10),
            vec2(0, -10))
			);

}

void LaserBall::update(float dt) {
	getAnimator().playAnimation(dt);


	if (getAnimator().isAnimationEnded() && (getCurrentASIndex() == BLaserBallAnimationSet::BLB_BOOM)) {
		setFree(true);
	}

	if (!getAbleMovement()) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void LaserBall::explodeMap(){
    // explode();
}

void LaserBall::explode() {

    setCurrentASIndex(BLaserBallAnimationSet::BLB_BOOM);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
    setAbleMovement(false);
    setDisabled(true);
    setFree(true);
}
