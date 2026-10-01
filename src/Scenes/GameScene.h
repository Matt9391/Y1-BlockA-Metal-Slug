#pragma once
#include "CustomScene.h"
#include <Player.h>

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
	void addNewEntity(Entity* e);
	void freeEntity(int index);
	Player player;
	static const int MAXENTITIES = 150;

	Entity* spawnedEntities[MAXENTITIES];
	Map map;
	bool loseCondition;
	int secondsLeft;
	float elapsedLoseTime;
};

