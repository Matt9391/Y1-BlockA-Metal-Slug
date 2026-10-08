#pragma once
#include <Enemy.h>

enum HelicopterAnimationSet{
    HAS_MOVE_FWD,
    HAS_MOVE_BWD,
    HAS_TRANSITION_FWD,
    HAS_TRANSITION_BWD,
    HAS_BOOM,
    HAS_COUNTS
};

class Bullet;
class Renderer;


class Helicopter : public Enemy{
public: 
    Helicopter(vec2 pos);
    ~Helicopter() override;

    void loadGFX() override;

	void update(float dt) override;
    void freeBullet(int i);

    void addRenderDatas(Renderer& renderer);

    int getMaxBullets() const;
    

    Bullet* getBullet(int i) const;

    void takeHit();
private:
    bool shoot();

    
    float elapsedTime;
    static const int SHOOTCOOLDOWN = 800;
	static const int MAXBULLETS = 50;
	static const int MINDIST = 10;
    Bullet* bullets[MAXBULLETS];
    int bulletsCount;
    float bulletSpeed;
    
    vec2 shootOffset;

    float startY;
    float maxY;
    int lives;
};