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
	~Player() override;

	void loadGFX() override;

	void update(float dt) override;

private:
	
};

