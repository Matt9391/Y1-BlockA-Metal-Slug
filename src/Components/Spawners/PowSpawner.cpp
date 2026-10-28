#include "precomp.h"
#include "PowSpawner.h"
#include <Pow.h>

PowSpawner::PowSpawner(vec2 pos, vec2 size, float spawnDelay, int powType) :
	Spawner(pos, size, spawnDelay),
	powType(powType),
	nOfPow(1)
{
}


// Same timing logic as EnemySpawner (with a 0 ms delay it checks every frame).
void PowSpawner::update(float dt) {
	addTimer(dt);
	if (getTimer() > getSpawnDelay()) {

		if (abs(getDistToPlayer()) < SPAWNRANGE) {
			setSpawnEntity(true);
		}
		setTimer(0);
	}
}

Entity* PowSpawner::createEntity() {
	if (!getSpawnEntity()) return nullptr;
	if (getSpawnedNumber() >= nOfPow) return nullptr;
	Entity* pow{ nullptr };
	
	pow = new Pow(getPos()); //only one POW
	
	setSpawnEntity(false);
	addSpawnedNumber();

	return pow;
}
