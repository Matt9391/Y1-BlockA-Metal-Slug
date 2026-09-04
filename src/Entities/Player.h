#pragma once
#include <Entity.h>

class Player : public Entity
{
public:
	Player(vec2 pos);

	void update(float dt) override;
	void display(Surface* screen) override;

private:

};

