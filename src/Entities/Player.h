#pragma once
#include <Entity.h>
#include <AnimationSet.h>
#include <PlayerAnimations.h>

class Tmpl8::Sprite;
class ResourceManager;

class Player : public Entity
{
public:
	Player(vec2 pos);

	void loadGFX(ResourceManager& resourceManager) override;

	void update(float dt) override;
	void display(float dt, Surface* screen) override;

private:
	AnimationSet animationSets[PlayerAnimations::PA_COUNTS];
};

