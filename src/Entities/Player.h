#pragma once
#include <Entity.h>

class Tmpl8::Sprite;
class ResourceManager;

class Player : public Entity
{
public:
	Player(vec2 pos);

	void getSprites(ResourceManager& resourceManager) override;

	void update(float dt) override;
	void display(Surface* screen) override;

private:
	Sprite* bodySprite;
};

