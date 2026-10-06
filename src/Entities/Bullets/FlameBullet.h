#pragma once
#include <Bullet.h>

enum BFlameAnimationSet{
    BF_SHOOT,
    BF_BOOM,
    BF_BOOM_STILL,
    BF_COUNTS
};

class FlameBullet : public Bullet{
public:
    FlameBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	~FlameBullet() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap();
};