#pragma once
#include "CustomScene.h"

class Tmpl8::Surface;

class MenuScene : public CustomScene
{
public:
	MenuScene(Surface* screen, Renderer& renderer, InputManager& inputManager, AudioManager& audioManager, ResourceManager& resourceManager_);

	void init() override;
	void exit() override;

	void update(float dt) override;

private:
	int secondsLeft;
	float elapsedTime;
	
};

