#pragma once

#include <Entity.h>
#include <InputManager.h>
#include <TankState.h>
#include <RenderData.h>

class Player;
class Bullet;
class Renderer;
enum BulletType : int;

class Tank : public Entity{
public:
    Tank(vec2 pos, const InputManager& inputManager_);
	~Tank() override;
	void loadGFX() override;

	void update(float dt) override;

    void enterPlayer(Player* player_);

    const TankStates::TankInput getTankInput() const;

    bool hasPlayer() const;

    void takeHit();

    Bullet* getBullet(int i) const;
    int getMaxBullets() const;
    void freeBullet(int i);
    
    void addRenderDatas(Renderer& renderer);

private:
    bool shoot(BulletType bulletType);
    void ejectPlayer();
    
	const InputManager& inputManager; //Const so it can only call const methods
    TankStates::TankState* state;

    Player* player;

    bool gotHit;
    bool dead;
    int hp;
    vec2 playerOffset;

    static const int MAXBULLETS = 30;
    Bullet* bullets[MAXBULLETS];
    int bulletsCount;
    float bulletSpeed;

    vec2 shootOffset;
    vec2 shootBulletOffset;
    vec2 shootDir;

    float angle;
    float angleIncr;
    float angleFrame;

    RenderData shooterRs;

    bool aimUp;
};