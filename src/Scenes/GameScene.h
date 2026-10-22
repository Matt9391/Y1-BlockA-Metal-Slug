#pragma once

#include <CustomScene.h>        
#include <Player.h>             
#include <Map.h>                
#include <Entity.h>              
#include <RenderData.h>         
#include <ParallaxRenderData.h>
#include <AnimatedDecoration.h>        

class Tank;
class Enemy;
class Bullet;
class RebelSoldier;
class Pow;
class Helicopter;
class Boss;

class GameScene : public CustomScene {
public:
	GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager, AudioManager& audioManager, ResourceManager& resourceManager, const Map& map_);
	~GameScene() override;

	void init() override;
	void exit() override;
	void update(float dt) override;

private:
	// ---- Entity storage ----
	void addNewEntity(Entity* e);
	void freeEntity(int index);

	// ---- NEW: refactored pieces of update() ----
	void renderHUD(float dt);

	void resolveBulletVsEntities(Bullet* b);
	void damagePlayerOrTank();

	void loadEnemySensors(Enemy* enemy, vec2 targetPos);

	void handleRebelSoldier(RebelSoldier* enemy);
	void handlePow(Pow* pow);
	void handleLootDrop(Entity* e, const Collider& playerColliderInFront);
	void handleHelicopter(Helicopter* h);
	void handleBoss(Boss* bs);
	void handleTank(Tank* tank);

	// ---- State ----
	// Member order matches the constructor's initializer list in GameScene.cpp.
	Player player;

	static const int WINCOUNTDOWN = 1000;
	
	bool loseCondition;
	bool winCondition;
	bool justWin;
	int secondsLeft;
	float elapsedLoseTime;
	float winTimer;
	
	static const int MAXENTITIES = 150;
	// MAXENTITIES: keep wherever you already define it
	Entity* spawnedEntities[MAXENTITIES];

	// NEW: set once in init(), nulled in freeEntity(). Never derived from an array index.
	Tank* tankRef = nullptr;

	const Map& map;             

	ParallaxRenderData parallaxRenderData;

	static const int MAWWATERDECORATION = 4;
	AnimatedDecoration waterDecorations[MAWWATERDECORATION];

	int nTilesLimit1Camera;
	int nTilesLimit2Camera;
};