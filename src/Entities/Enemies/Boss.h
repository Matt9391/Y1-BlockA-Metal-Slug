#pragma once
#include <Enemy.h>
#include <BossState.h>


class Bullet;
class Renderer;
enum BulletType : int;

// Boss - the final enemy: a big ship whose cannon moves between a high and a low position.
// At 50 HP or more it fires 3 cannon balls per position; below 50 HP a laser beam (high) or a laser ball (low).
// The behaviour lives in BossStates (BossState.cpp). Destroying it wins the level.
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

    // bool shootBeam(); // DONE: MERGE these function together
    // bool shootCannon();
    // bool shootLaserBall();
    bool shoot(BulletType bulletType); // spawn a bullet of the given type at the cannon

    int getHP() const;

    void setShootOffsetY(float offset); // set the cannon height (HIGH_SHOOT_OFFSET / LOW_SHOOT_OFFSET)

    static constexpr float HIGH_SHOOT_OFFSET = 10; // px, cannon in the top position
    static constexpr float LOW_SHOOT_OFFSET = 41.5f; // px, cannon in the bottom position

private:
    BossStates::BossState* state; // current state object

    static const int MAXBULLETS = 30;
    Bullet* bullets[MAXBULLETS];
    int bulletsCount;
    float bulletSpeed;

    vec2 shootOffset; // bullet spawn point relative to the collider


    int HP; // hits left; below 0 the boss dies
};