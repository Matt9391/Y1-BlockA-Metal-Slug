#pragma once
#include <Bullet.h>

enum BFlameAnimationSet{
    BF_SHOOT,
    BF_SHOOT_25,
    BF_SHOOT_45,
    BF_SHOOT_75,
    BF_SHOOT_90,
    BF_BOOM,
    BF_BOOM_25,
    BF_BOOM_45,
    BF_BOOM_75,
    BF_BOOM_90,
    BF_BOOM_STILL,
    BF_COUNTS
};

class FlameBullet : public Bullet{
public:
    FlameBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed, float angle);
	~FlameBullet() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap();
private:
    int getAngleAnimationIndex(bool boom = false) const;

    bool isShootAnimation() const;
    bool isBoomAnimation() const;

    float angle;    
};