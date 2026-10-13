#pragma once
#include <Enemy.h>
#include <BossState.h>


class Bullet;
class Renderer;
enum BulletType : int;

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

    void takeHit();

    void moveShootOffset(vec2 incr);
    // bool shootBeam(); // DONE: MERGE these function together
    // bool shootCannon();
    // bool shootLaserBall();
    bool shoot(BulletType bulletType);

    int getHP() const;
private:
    BossStates::BossState* state;

    static const int MAXBULLETS = 30;
    Bullet* bullets[MAXBULLETS];
    int bulletsCount;
    float bulletSpeed;

    vec2 shootOffset;

    int HP;

};