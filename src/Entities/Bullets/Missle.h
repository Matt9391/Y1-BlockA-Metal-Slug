#pragma once
#include <Bullet.h>

enum BMissleAnimationSet{
    BM_SHOOT,
    BM_BOOM,
    BM_COUNTS
};

class Missle : public Bullet{
public:
    Missle(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	~Missle() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap(); 
};