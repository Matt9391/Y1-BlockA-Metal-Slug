#pragma once
#include <vec2.h>

class Entity;

class Spawner {
public:
	Spawner(vec2 pos, vec2 size, float spawnDelay);
	virtual ~Spawner();

	virtual void update(float dt);

	const vec2& getPos() const;
	const vec2& getSize() const;
protected:
	virtual Entity* createEntity() = 0;

private:
	vec2 pos;
	vec2 size;

	Entity* spawnedEntities;

	float spawnDelay;
	float timer;
};