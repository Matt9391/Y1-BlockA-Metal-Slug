#pragma once
#include <Bullet.h>

enum BCannonBallAnimationSet{
    BCB_SHOOT,
    BCB_BOOM,
    BCB_COUNTS
};

// CannonBall - boss projectile: follows a fixed arc toward the player (no physics); the sprite is "rotated"
// by picking the frame that matches the flight direction.
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
    float duration; // ms to complete the arc
    vec2 startPos; // start of the arc

    float arcWidth; // horizontal distance covered by the arc, px
    float peakHeight; // px
    float frameAngle; // degrees per sprite frame
};