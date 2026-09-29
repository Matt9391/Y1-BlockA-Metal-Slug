#include "precomp.h"
#include "EnemySpawner.h"
#include <Enemies/RebelSoldier.h>

EnemySpawner::EnemySpawner(vec2 pos, vec2 size, float spawnDelay, int enemyType, int nOfEnemy) :
	Spawner(pos, size, spawnDelay),
	enemyType(enemyType),
	nOfEnemy(nOfEnemy)
{
}


void EnemySpawner::update(float dt) {
	addTimer(dt);
	if (getTimer() > getSpawnDelay()) {

		if (abs(getDistToPlayer()) < SPAWNRANGE) {
			setSpawnEntity(true);
		}
		setTimer(0);
	}
}

Entity* EnemySpawner::createEntity() {
	if (!getSpawnEntity()) return nullptr;
	if (getSpawnedNumber() >= nOfEnemy) return nullptr;
	Entity* enemy{ nullptr };
	switch (enemyType)
	{
	case 0:
		enemy = new RebelSoldier(getPos());
		break;
	default:
		break;
	}

	setSpawnEntity(false);
	addSpawnedNumber();

	return enemy;
}
