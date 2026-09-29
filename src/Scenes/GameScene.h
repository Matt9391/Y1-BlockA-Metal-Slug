#pragma once
#include "CustomScene.h"
#include <Player.h>
#include <Pow.h>
#include <Enemies/RebelSoldier.h>
#include <Map.h>
#include <Printer.h>


class GameScene : public CustomScene
{
public:
	GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager);
	~GameScene();
	
	void init() override;
	void exit() override;
	
	void update(float dt) override;
	void display(float dt) override;

private:
	Player player;
	RebelSoldier soldier;
	Entity* spawnedEntities;

	Pow pow;
	Map map;
	bool loseCondition;
	int secondsLeft;
	float elapsedLoseTime;
};

