#include "precomp.h"
#include "EnemySpawner.h"
#include <Enemies/RebelSoldier.h>
#include <Enemies/Helicopter.h>
#include <RebelSoldierType.h>

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
		case RebelSoldierType::RST_BASE:
		enemy = new RebelSoldier(getPos(), rsPreset.getRebelSoliderPreset(RebelSoldierType::RST_BASE));
		break;
		case RebelSoldierType::RST_MELEE:
		enemy = new RebelSoldier(getPos(), rsPreset.getRebelSoliderPreset(RebelSoldierType::RST_MELEE));
		break;
		case RebelSoldierType::RST_MELEE_GRENADE:
		enemy = new RebelSoldier(getPos(), rsPreset.getRebelSoliderPreset(RebelSoldierType::RST_MELEE_GRENADE));
		break;
		case RebelSoldierType::HELICOPTER:
		enemy = new Helicopter(getPos());
		break;
	default:
		break;
	}

	setSpawnEntity(false);
	addSpawnedNumber();

	return enemy;
}
