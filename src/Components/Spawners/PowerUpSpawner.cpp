#include "precomp.h"
#include "PowerUpSpawner.h"
#include <LootDrops/PowerUp.h>



PowerUpSpawner::PowerUpSpawner(vec2 pos, vec2 size, float spawnDelay, int spawnState) :
	Spawner(pos, size, spawnDelay),
	spawnState(spawnState),
	nOfPowerUp(1)
{
}


void PowerUpSpawner::update(float dt) {
	addTimer(dt);
	if (getTimer() > getSpawnDelay()) {

		if (abs(getDistToPlayer()) < SPAWNRANGE) {
			setSpawnEntity(true);
		}
		setTimer(0);
	}
}

Entity* PowerUpSpawner::createEntity() {
	if (!getSpawnEntity()) return nullptr;
	if (getSpawnedNumber() >= nOfPowerUp) return nullptr;
	Entity* powerup{ nullptr };

    powerup = new PowerUp(getPos(), static_cast<PowerUpState>(spawnState));

	setSpawnEntity(false);
	addSpawnedNumber();

	return powerup;
}
