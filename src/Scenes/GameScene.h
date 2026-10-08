#pragma once
#include "CustomScene.h"
#include <Player.h>

#include <Map.h>
#include <Printer.h>


class GameScene : public CustomScene
{
public:
	GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager, AudioManager& audioManager, const Map& map_);
	~GameScene();
	
	void init() override;
	void exit() override;
	
	void update(float dt) override;

private:
	void addNewEntity(Entity* e);
	void freeEntity(int index);
	Player player;
	static const int MAXENTITIES = 150;

	Entity* spawnedEntities[MAXENTITIES];
	const Map& map;
	const ParallaxRenderData parallaxRenderData;
	bool loseCondition;
	bool winCondition;
	bool justWin;
	int secondsLeft;
	float elapsedLoseTime;

	RenderData waterfall;
	RenderData waterfallBottom;
	Animator anim;
	Animator anim2;

	int nTilesLimit1Camera;
	int nTilesLimit2Camera;
};

