#pragma once
#include <Bullet.h>

// Animation sets of the pistol bullet: flying (horizontal / vertical) and the boom for each direction.
enum BPistolAnimationSet{
    BP_SHOOT,
    BP_SHOOT_90, // flying vertically
    BP_BOOM,
    BP_BOOM_90, // boom when going up
    BP_BOOM_D90, // boom when going down
    BP_COUNTS
};

// PistolBullet - the player's basic bullet: flies in a straight line (4 directions) and explodes on contact.
class PistolBullet : public Bullet{
public:
    PistolBullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	~PistolBullet() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode(); 
	void explodeMap(); 
private:
	int getAngleAnimationIndex(bool boom = false) const; // pick the set that matches the direction (flying or boom)
	bool isBoomAnimation() const;
};