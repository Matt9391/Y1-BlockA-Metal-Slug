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
	setCurrentASIndex(getAngleAnimationIndex());
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

    getAnimationSets()[BPistolAnimationSet::BP_SHOOT_90] = AnimationSet(
    1,
    AnimationLayer(ResourceID::ID_PLAYER_BULLET_PISTOL_90,
        ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL_90,
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

    getAnimationSets()[BPistolAnimationSet::BP_BOOM_90] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_PISTOL_BOOM_90,
            ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL_BOOM_90,
            50,
            vec2(0, 0),
            vec2(0, 0))
			);

    getAnimationSets()[BPistolAnimationSet::BP_BOOM_D90] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_PISTOL_BOOM_D90,
            ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL_BOOM_D90,
            50,
            vec2(0, 0),
            vec2(0, 0))
			);

}

void PistolBullet::update(float dt) {
	getAnimator().playAnimation(dt);


	if (getAnimator().isAnimationEnded() && isBoomAnimation()) {
		setFree(true);
	}

	if (!getAbleMovement()) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void PistolBullet::explodeMap(){
    explode();
}

void PistolBullet::explode() {
    setCollider(vec2(15, 15), vec2(0, 0));
    setCurrentASIndex(getAngleAnimationIndex(true));
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], getDir().x < 0);
    setAbleMovement(false);
    setDisabled(true);

}


int PistolBullet::getAngleAnimationIndex(bool boom) const
{
    vec2 direction = getDir();

    bool isVertical = direction.y != 0.f;

    if (!isVertical)
    {
        return boom
            ? BPistolAnimationSet::BP_BOOM
            : BPistolAnimationSet::BP_SHOOT;
    }

    if (!boom)
    {
        return BPistolAnimationSet::BP_SHOOT_90;
    }

    return direction.y < 0.0f
        ? BPistolAnimationSet::BP_BOOM_90
        : BPistolAnimationSet::BP_BOOM_D90;
}

bool PistolBullet::isBoomAnimation() const
{
    int index = getCurrentASIndex();

    return index == BPistolAnimationSet::BP_BOOM ||
           index == BPistolAnimationSet::BP_BOOM_90 ||
           index == BPistolAnimationSet::BP_BOOM_D90;
}