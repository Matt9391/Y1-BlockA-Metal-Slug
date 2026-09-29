#include "precomp.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(vec2 pos, vec2 size, float spawnDelay, int enemyType, int nOfEnemy) :
	Spawner(pos, size, spawnDelay),
	enemyType(enemyType),
	nOfEnemy(nOfEnemy)
{
}


void EnemySpawner::update(float dt) {

}

Entity* EnemySpawner::createEntity() {
	return nullptr;
}
