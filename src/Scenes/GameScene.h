#pragma once
#include "CustomScene.h"
#include <Player.h>


class GameScene : public CustomScene
{
public:
	GameScene(Surface* screen, ResourceManager& resourceManager);
	
	void init() override;
	void exit() override;
	
	void update(float dt) override;
	void display(float dt) override;

private:
	Player player;
};

