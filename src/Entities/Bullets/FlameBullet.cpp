#include "precomp.h"
#include "FlameBullet.h"
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <BulletType.h>

FlameBullet::FlameBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed, float angle) :
    Bullet(pos,needsRigidBody,dir,bulletType,bulletSpeed),
    angle(angle)
{ 
	setDir(dir);
    setCollider(vec2(35, 25), vec2(0, 0));

	getAnimationSets() = new AnimationSet[BFlameAnimationSet::BF_COUNTS];
	loadGFX();

    setCurrentASIndex(getAngleAnimationIndex());

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
    getAnimationSets()[BFlameAnimationSet::BF_SHOOT_25] = AnimationSet(
			1,
			AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_25,
				ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_25,
			40,
			vec2(-15, -25),
            vec2(-15, -25))
    );
    getAnimationSets()[BFlameAnimationSet::BF_SHOOT_45] = AnimationSet(
			1,
			AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_45,
				ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_45,
			40,
            vec2(-15, -25),
            vec2(-15, -25))
    );
    getAnimationSets()[BFlameAnimationSet::BF_SHOOT_75] = AnimationSet(
			1,
			AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_75,
				ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_75,
			40,
            vec2(-15, -25),
            vec2(-15, -25))
    );
    getAnimationSets()[BFlameAnimationSet::BF_SHOOT_90] = AnimationSet(
			1,
			AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_90,
				ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_90,
			40,
            vec2(-15, -10),
            vec2(-15, -10))
    );
        
    getAnimationSets()[BFlameAnimationSet::BF_BOOM] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM,
            ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM,
            50,
            vec2(-15, -25),
            vec2(-15, -25))
    );
    getAnimationSets()[BFlameAnimationSet::BF_BOOM_25] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM_25,
            ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM_25,
            50,
            vec2(-15, -25),
            vec2(-15, -25))
    );
    getAnimationSets()[BFlameAnimationSet::BF_BOOM_45] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM_45,
            ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM_45,
            50,
            vec2(-15, -25),
            vec2(-15, -25))
    );
    getAnimationSets()[BFlameAnimationSet::BF_BOOM_75] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM_75,
            ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM_75,
            50,
            vec2(-15, -25),
            vec2(-15, -25))
    );
    getAnimationSets()[BFlameAnimationSet::BF_BOOM_90] = AnimationSet(
        1,
        AnimationLayer(ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM_90,
            ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM_90,
            50,
            vec2(-15, -10),
            vec2(-15, -10))
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

	if (getAnimator().isAnimationEnded() && isShootAnimation()) {
		explode();
	}

	if (getAnimator().isAnimationEnded() && isBoomAnimation()) {
		setFree(true);
	}

	if (!getAbleMovement()) return;

	this->addToPos(getDir() * dt * getRigidBody()->getSpeed());

}

void FlameBullet::explodeMap(){
    setDisabled(true);
    setDir(vec2(-0.01f * getDir().x, 0.f));
    setCurrentASIndex(BFlameAnimationSet::BF_BOOM_STILL);
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], getDir().x < 0);
}

void FlameBullet::explode() {

    setCurrentASIndex(getAngleAnimationIndex(true));
    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], getDir().x < 0);

}

int FlameBullet::getAngleAnimationIndex(bool boom) const
{
    if (angle == 0.0f)
    {
        return boom
            ? BFlameAnimationSet::BF_BOOM
            : BFlameAnimationSet::BF_SHOOT;
    }
    else if (angle > 0.0f && angle <= 25.0f)
    {
        return boom
            ? BFlameAnimationSet::BF_BOOM_25
            : BFlameAnimationSet::BF_SHOOT_25;
    }
    else if (angle > 25.0f && angle <= 45.0f)
    {
        return boom
            ? BFlameAnimationSet::BF_BOOM_45
            : BFlameAnimationSet::BF_SHOOT_45;
    }
    else if (angle > 45.0f && angle <= 75.0f)
    {
        return boom
            ? BFlameAnimationSet::BF_BOOM_75
            : BFlameAnimationSet::BF_SHOOT_75;
    }
    else if (angle > 75.0f && angle <= 90.0f)
    {
        return boom
            ? BFlameAnimationSet::BF_BOOM_90
            : BFlameAnimationSet::BF_SHOOT_90;
    }

    return boom
        ? BFlameAnimationSet::BF_BOOM
        : BFlameAnimationSet::BF_SHOOT;
}

bool FlameBullet::isShootAnimation() const
{
    int index = getCurrentASIndex();

    return index == BFlameAnimationSet::BF_SHOOT ||
           index == BFlameAnimationSet::BF_SHOOT_25 ||
           index == BFlameAnimationSet::BF_SHOOT_45 ||
           index == BFlameAnimationSet::BF_SHOOT_75 ||
           index == BFlameAnimationSet::BF_SHOOT_90;
}

bool FlameBullet::isBoomAnimation() const
{
    int index = getCurrentASIndex();

    return index == BFlameAnimationSet::BF_BOOM ||
           index == BFlameAnimationSet::BF_BOOM_25 ||
           index == BFlameAnimationSet::BF_BOOM_45 ||
           index == BFlameAnimationSet::BF_BOOM_75 ||
           index == BFlameAnimationSet::BF_BOOM_90 ||
           index == BFlameAnimationSet::BF_BOOM_STILL;
}
