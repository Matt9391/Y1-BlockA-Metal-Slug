#pragma once
#include "Scene.h"

class GameScene : Scene
{
public:
	GameScene(Surface* screen);
	
	void init() override;
	void exit() override;
	
	void update(float dt) override;
	void display() override;
};

