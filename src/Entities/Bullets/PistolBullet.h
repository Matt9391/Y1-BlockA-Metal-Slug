#pragma once
#include <Bullet.h>

enum BPistolAnimationSet{
    BP_SHOOT,
    BP_SHOOT_90,
    BP_BOOM,
    BP_BOOM_90,
    BP_BOOM_D90,
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
private:
	int getAngleAnimationIndex(bool boom = false) const;
	bool isBoomAnimation() const;
};