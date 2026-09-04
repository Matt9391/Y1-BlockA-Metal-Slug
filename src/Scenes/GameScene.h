#pragma once
#include "CustomScene.h"
#include <Player.h>


class GameScene : public CustomScene
{
public:
	GameScene(Surface* screen);
	
	void init() override;
	void exit() override;
	
	void update(float dt) override;
	void display() override;

private:
	Player player;
};

