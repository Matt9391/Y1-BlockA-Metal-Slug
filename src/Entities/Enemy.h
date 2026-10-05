#pragma once
#include <Entity.h>

struct EnemySensor {
	float distToPlayer;
	bool allyDiedNearby;
	bool wallAhead;
	bool platformAbove;
	bool isGrounded;
	bool animationEnded;
	bool alive;
};

class Enemy : public Entity {

public:
	Enemy(vec2 pos, EntityType entityType);
	//~Enemy() override;
	void setFlip(bool flip);
	bool getFlip() const;
	void setAttacking(bool flip);
	bool getAttacking() const;

	void loadSensors(vec2 playerPos, bool wallAhead);

	const EnemySensor& getSensors() const;

	void setAlive(bool alive_);
	bool getAlive() const;

	

private:
	EnemySensor sensors;
	bool flip;
	bool attacking;
	bool alive;
	//other stuff
};



