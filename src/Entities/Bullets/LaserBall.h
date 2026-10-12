#pragma once
#include <Bullet.h>

enum BLaserBallAnimationSet{
    BLB_SHOOT,
    BLB_BOOM,
    BLB_COUNTS
};

class LaserBall : public Bullet{
public:
    LaserBall(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	~LaserBall() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap(); 
};