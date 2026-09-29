#pragma once
#include <Spawner.h>


class EnemySpawner : public Spawner {
public:
	EnemySpawner(vec2 pos, vec2 size, float spawnDelay, int enemyType, int nOfEnemy);

	void update(float dt) override;
private:
	Entity* createEntity() override;

	int enemyType;
	int nOfEnemy;

	static const int SPAWNRANGE = 300;
};
