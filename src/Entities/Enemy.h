#pragma once
#include <Entity.h>

struct EnemySensor {
	float distToPlayer;
	bool allyDiedNearby;
	bool wallAhead;
	bool platformAbove;
	bool isGrounded;
	bool animationEnded;
};

class Enemy : public Entity {

public:
	Enemy(vec2 pos);
	//~Enemy() override;
	void setFlip(bool flip);
	bool getFlip() const;

	void loadSensors(vec2 playerPos, bool wallAhead);

	const EnemySensor& getSensors() const;

private:
	EnemySensor sensors;
	bool flip;
	int health;
	//other stuff
};



