#pragma once
#include <Enemy.h>

enum HelicopterAnimationSet{
    HAS_MOVE_FWD, // flying left, toward the player (the sprites face left)
    HAS_MOVE_BWD, // flying right, tilted backwards
    HAS_TRANSITION_FWD, // tilting from backwards to forwards
    HAS_TRANSITION_BWD, // tilting from forwards to backwards
    HAS_BOOM, // explosion
    HAS_COUNTS
};

class Bullet;
class Renderer;


// Helicopter - flying enemy. Flies toward the player, rises or sinks depending on its direction, and drops
// 3 missiles every SHOOTCOOLDOWN ms. Destroying it unlocks the rest of the level (the camera can scroll further).
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

    void takeHit(); // lose one life (it explodes when lives < 0)
private:
    bool shoot();

    
    float elapsedTime;
    static const int SHOOTCOOLDOWN = 800; // ms between missile volleys
	static const int MAXBULLETS = 50;
	static const int MINDIST = 10; // px: closer than this to the player, it keeps its current animation
    Bullet* bullets[MAXBULLETS];
    int bulletsCount;
    float bulletSpeed;
    
    vec2 shootOffset; // missile spawn point relative to pos

    float startY; // highest point (it never flies above its spawn height)
    float maxY; // lowest point (spawn height + 25 px)
    int lives; // hits it can take
};