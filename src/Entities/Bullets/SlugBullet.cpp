#include "precomp.h"
#include "SlugBullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

SlugBullet::SlugBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float speed_) :
    Bullet(pos, needsRigidBody, dir, bulletType, speed_),
    frameAngle(360.f / static_cast<float>(ResourceIDFrames::IDF_SLUG_BULLET)) // 64 frames -> 5.625, 16 frames -> 22.5
{
    setDir(dir);

    setCollider(vec2(8, 4), vec2(0, 0));   
    getAnimationSets() = new AnimationSet[BSB_COUNTS];
    loadGFX();
    setCurrentASIndex(BSB_SHOOT);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

    float angle = atan2f(dir.y, dir.x) * 180.f / PI;
    if (angle < 0.f) angle += 360.f;

    int frame = static_cast<int>(roundf(angle / frameAngle)) % static_cast<int>(ResourceIDFrames::IDF_SLUG_BULLET); // 360 deg wraps to frame 0

    getAnimator().setFrame(frame);

    getRigidBody()->setSpeed(speed_);
}

SlugBullet::~SlugBullet() {
    delete[] getAnimationSets();
}

void SlugBullet::loadGFX() {

    // bullet_ms2_49x49_64dir.png: 64 frames of 49x49, pivot (24, 24) = bullet head
    // (bullet_ms1_49x49_16dir.png works too: same cell and pivot, set IDF_SLUG_BULLET = 16)
    getAnimationSets()[BSB_SHOOT] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_SLUG_BULLET,
            ResourceIDFrames::IDF_SLUG_BULLET,   // 64
            100,
            vec2(-24, -24),
            vec2(-24, -24))
    );
    getAnimationSets()[BSB_BOOM] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_SLUG_BULLET_BOOM,
            ResourceIDFrames::IDF_SLUG_BULLET_BOOM,   // 10
            100,
            vec2(0, 0),
            vec2(0, 0))
    );
}

void SlugBullet::update(float dt) {
    // no playAnimation() while flying: the frames are directions, playing them would spin the bullet
    if (getCurrentASIndex() == BSB_BOOM) getAnimator().playAnimation(dt);
	setColliderSprite();


    if (getAnimator().isAnimationEnded() && getCurrentASIndex() == BSB_BOOM) {
        setFree(true);
    }

    if (!getAbleMovement()) return;

    this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void SlugBullet::explodeMap() {
    explode();
}

void SlugBullet::explode() {

    setAbleMovement(false);
    setCurrentASIndex(BSB_BOOM);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

}