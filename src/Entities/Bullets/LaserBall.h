#pragma once
#include <Bullet.h>

enum BLaserBallAnimationSet{
    BLB_SHOOT,
    BLB_BOOM,
    BLB_COUNTS
};

// LaserBall - boss low attack: a ball that flies straight to the left and goes through walls.
class LaserBall : public Bullet{
public:
    LaserBall(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	~LaserBall() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap(); 
}; 