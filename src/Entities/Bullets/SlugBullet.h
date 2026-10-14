#pragma once
#include <Bullet.h>

enum BSlugBulletAnimationSet {
    BSB_SHOOT,
    BSB_BOOM,
    BSB_COUNTS
};

class SlugBullet : public Bullet {
public:
    SlugBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float speed_);
    ~SlugBullet() override;

    void loadGFX() override;

    void update(float dt) override;

    void explode();
    void explodeMap();
private:
    float frameAngle;
};