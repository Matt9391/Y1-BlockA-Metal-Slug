#pragma once
#include <Bullet.h>

enum BCannonBallAnimationSet{
    BCB_SHOOT,
    BCB_BOOM,
    BCB_COUNTS
};

class CannonBall : public Bullet{
public:
    CannonBall(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float duration_, float width_);
	~CannonBall() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap(); 
private:
    float elapsedTime;
    float duration;
    vec2 startPos;

    float arcWidth;
    float peakHeight;
    float frameAngle;
};