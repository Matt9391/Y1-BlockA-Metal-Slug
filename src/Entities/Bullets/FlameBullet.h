#pragma once
#include <Bullet.h>

// Animation sets of a flame: flying and dissipating ("boom") for each aim angle, plus BOOM_STILL for when it hits a wall.
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

// FlameBullet - one burst of the flame thrower. The sprite is picked from the aim angle (0, 25, 45, 75, 90 degrees).
// Hitting a soldier does not disable it, so one flame can burn several enemies before it fades out.
class FlameBullet : public Bullet{
public:
    FlameBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed, float angle);
	~FlameBullet() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode() override;
	void explodeMap() override;
private:
    int getAngleAnimationIndex(bool boom = false) const;

    bool isShootAnimation() const;
    bool isBoomAnimation() const;

    float angle;    // aim angle in degrees, from Gun::setGunAngle
}; 