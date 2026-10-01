#pragma once
#include "CustomScene.h"


#include <Animator.h>

class Tmpl8::Surface;

class GameOverScene : public CustomScene
{
public:
	GameOverScene(Surface* screen, Renderer& renderer, InputManager& inputManager);

	void init() override;
	void exit() override;

	void update(float dt) override;
	void display(float dt) override;

private:
	int secondsLeft;
	float elapsedTime;
    Animator animator;
    AnimationSet as;
};

