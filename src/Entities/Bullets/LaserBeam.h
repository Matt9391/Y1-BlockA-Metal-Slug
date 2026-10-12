#pragma once
#include <Bullet.h>

enum BLaserBeamAnimationSet{
    BLBe_SHOOT,
    BLBe_BOOM,
    BLBe_COUNTS
};

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