#include "precomp.h"
#include "PowSpawner.h"
#include <Pow.h>

PowSpawner::PowSpawner(vec2 pos, vec2 size, float spawnDelay, int powType) :
	Spawner(pos, size, spawnDelay),
	powType(powType),
	nOfPow(1)
{
}


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
	switch (powType)
	{
	case 0:
		pow = new Pow(getPos());
		break;
	case 1:
		pow = new Pow(getPos());
		break;
	default:
		break;
	}

	setSpawnEntity(false);
	addSpawnedNumber();

	return pow;
}
