#pragma once
#include <Enemy.h>

enum HelicopterAnimationSet{
    HAS_MOVE,
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

private:
    bool shoot();
    float elapsedTime;
    static const int SHOOTCOOLDOWN = 400;
	static const int MAXBULLETS = 50;
    Bullet* bullets[MAXBULLETS];
    int bulletsCount;
    float bulletSpeed;
};