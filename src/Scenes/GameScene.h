#pragma once
#include "CustomScene.h"
#include <Player.h>
#include <Pow.h>
#include <Enemies/RebelSoldier.h>
#include <Map.h>
#include <Granade.h>


class GameScene : public CustomScene
{
public:
	GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager);
	
	void init() override;
	void exit() override;
	
	void update(float dt) override;
	void display(float dt) override;

private:
	Player player;
	RebelSoldier soldier;
	Pow pow;
	Map map;
	Granade gr;
};

