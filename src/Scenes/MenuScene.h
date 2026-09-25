#pragma once
#include "CustomScene.h"

class Tmpl8::Surface;

class MenuScene : public CustomScene
{
public:
	MenuScene(Surface* screen, Renderer& renderer, InputManager& inputManager);

	void init() override;
	void exit() override;

	void update(float dt) override;
	void display(float dt) override;

private:
	int secondsLeft;
	float elapsedTime;

};

