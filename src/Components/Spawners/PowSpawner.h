#pragma once
#include <Spawner.h>

class PowSpawner : public Spawner {
public:
	PowSpawner(vec2 pos, vec2 size, float spawnDelay, int powType);

	void update(float dt) override;
private:
	Entity* createEntity() override;

	int powType;
	int nOfPow;
	static const int SPAWNRANGE = 500;
};
