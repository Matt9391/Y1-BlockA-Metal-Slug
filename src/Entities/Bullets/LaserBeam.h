#pragma once
#include <Bullet.h>

enum BLaserBeamAnimationSet{
    BLBe_SHOOT,
    BLBe_BOOM,
    BLBe_COUNTS
};

// LaserBeam - boss high attack: a 300 px wide beam that appears in place, can only hurt during its first
// ~10 ms, and disappears after MAXTIME ms.
class LaserBeam : public Bullet{
public:
    LaserBeam(vec2 pos,BulletType bulletType);
	~LaserBeam() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	void explodeMap(); 
private:
    float elapsedTime;
    static const int MAXTIME = 300;
}; 