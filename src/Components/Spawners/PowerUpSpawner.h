#pragma once
#include <Spawner.h>

class PowerUpSpawner : public Spawner{
public:
	PowerUpSpawner(vec2 pos, vec2 size, float spawnDelay, int spawnState);

	void update(float dt) override;
private:
	Entity* createEntity() override;

	int spawnState;
	int nOfPowerUp;
	static const int SPAWNRANGE = 500;
};

