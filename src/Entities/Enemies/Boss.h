#pragma once
#include <Enemy.h>
#include <BossState.h>


class Bullet;
class Renderer;


class Boss : public Enemy{
public:
    Boss(vec2 pos);
    ~Boss() override;

    void loadGFX() override;
    
	void update(float dt) override;
    void freeBullet(int i);

    void addRenderDatas(Renderer& renderer);

    int getMaxBullets() const;
    

    Bullet* getBullet(int i) const;

    // void takeHit();

    void moveShootOffset(vec2 incr);
    bool shootCannon();
    bool shootLaserBall();

    int getLife() const;
private:
    BossStates::BossState* state;

    static const int MAXBULLETS = 30;
    Bullet* bullets[MAXBULLETS];
    int bulletsCount;
    float bulletSpeed;

    vec2 shootOffset;

    int life;

};