#pragma once
#include "CustomScene.h"
#include <Player.h>
#include <Map.h>


class GameScene : public CustomScene
{
public:
	GameScene(Surface* screen, Renderer& renderer);
	
	void init() override;
	void exit() override;
	

	
	void update(float dt) override;
	void display(float dt) override;

private:
	Player player;
	Map map;

};

