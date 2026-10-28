#pragma once
#include <vec2.h>

class Entity;

class Spawner {
public:
	Spawner(vec2 pos, vec2 size, float spawnDelay);
	virtual ~Spawner();

	virtual void init(); // reset the timer and the spawn counter (called when a new game starts)

	virtual void update(float dt);

	const vec2& getPos() const;
	const vec2& getSize() const;
	
	float getDistToPlayer() const; // signed X distance (player.x - spawner.x), set by the GameScene every frame
	void setDistToPlayer(float distToPlayer_);

	int  getSpawnedNumber() const;
	void addSpawnedNumber(); // count one more spawned entity

	virtual Entity* createEntity() = 0; // returns a NEW entity (the caller owns it) or nullptr
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

	float spawnDelay; // ms between two spawn checks
	float timer;
	float distToPlayer;
	bool spawnEntity; // "ready to spawn" flag, set by update()
	int spawnedNumber; // how many entities this spawner already created
};