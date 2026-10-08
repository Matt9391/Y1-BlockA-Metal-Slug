#pragma once
#include <vec2.h>

class Entity;

class Spawner {
public:
	Spawner(vec2 pos, vec2 size, float spawnDelay);
	virtual ~Spawner();

	virtual void init();

	virtual void update(float dt);

	const vec2& getPos() const;
	const vec2& getSize() const;
	
	float getDistToPlayer() const;
	void setDistToPlayer(float distToPlayer_);

	int  getSpawnedNumber() const;
	void addSpawnedNumber();

	virtual Entity* createEntity() = 0;
protected:

	float getSpawnDelay() const;

	float getTimer() const;
	void setTimer(float timer_);
	void addTimer(float dt);

	bool getSpawnEntity() const;
	void setSpawnEntity(bool spawnEntity_);

private:
	vec2 pos;
	vec2 size;

	float spawnDelay;
	float timer;
	float distToPlayer;
	bool spawnEntity;
	int spawnedNumber;
};