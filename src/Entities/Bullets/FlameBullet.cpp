#include "precomp.h"
#include "FlameBullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

FlameBullet::FlameBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed) :
    Bullet(pos,needsRigidBody,dir,bulletType,bulletSpeed)
{ 
	setDir(dir);
    setCollider(vec2(35, 25), vec2(0, 0));

	getAnimationSets() = new AnimationSet[BFlameAnimationSet::BF_COUNTS];
	loadGFX();
	setCurrentASIndex(BFlameAnimationSet::BF_SHOOT);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], dir.x < 0);
	getRigidBody()->setSpeed(bulletSpeed);
}

FlameBullet::~FlameBullet() {
	delete[] getAnimationSets();
}

void FlameBullet::loadGFX() {
	
    getAnimationSets()[BFlameAnimationSet::BF_SHOOT] = AnimationSet(
			1,
			AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER,
				ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER,
			40,
				vec2(0, -10),
				vec2(0, -10))
        );
        
        getAnimationSets()[BFlameAnimationSet::BF_BOOM] = AnimationSet(
            1,
            AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM,
                ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM,
                50,
                vec2(0, -10),
                vec2(0, -10))
        );
        getAnimationSets()[BFlameAnimationSet::BF_BOOM_STILL] = AnimationSet(
            1,
            AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM_STILL,
                ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM_STILL,
                70,
                vec2(0, -10),
                vec2(0, -10))
        );

}

void FlameBullet::update(float dt) {
	getAnimator().playAnimation(dt);

	if (getAnimator().isAnimationEnded() && getCurrentASIndex() == BFlameAnimationSet::BF_SHOOT) {
		explode();
	}

	if (getAnimator().isAnimationEnded() &&
     (getCurrentASIndex() == BFlameAnimationSet::BF_BOOM || getCurrentASIndex() == BFlameAnimationSet::BF_BOOM_STILL)) {
		setFree(true);
	}

	if (!getAbleMovement()) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void FlameBullet::explodeMap(){
    setDisabled(true);
    setDir(vec2(-0.01f * getDir().x, 0.f));
    setCurrentASIndex(BFlameAnimationSet::BF_BOOM_STILL);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
}

void FlameBullet::explode() {

    setCurrentASIndex(BFlameAnimationSet::BF_BOOM);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

}
