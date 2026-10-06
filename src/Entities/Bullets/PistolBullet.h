#pragma once
#include <Bullet.h>

enum BPistolAnimationSet{
    BP_SHOOT,
    BP_BOOM,
    BP_COUNTS
};

class PistolBullet : public Bullet{
public:
    PistolBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	~PistolBullet() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap(); 
};