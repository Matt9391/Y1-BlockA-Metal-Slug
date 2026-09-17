#pragma once
#include <Entity.h>


class Enemy : public Entity {

public:
	Enemy(vec2 pos);
	//~Enemy() override;

private:
	int health;
	//other stuff
};
