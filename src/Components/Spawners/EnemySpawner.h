#pragma once
#include <Spawner.h>
#include <RebelSoldierPresets.h>


// EnemySpawner - spawns up to nOfEnemy rebel soldiers (or a helicopter), one every spawnDelay ms,
// while the player is within SPAWNRANGE pixels.
class EnemySpawner : public Spawner {
public:
	EnemySpawner(vec2 pos, vec2 size, float spawnDelay, int enemyType, int nOfEnemy);

	void update(float dt) override;
private:
	Entity* createEntity() override;

	int enemyType; // RebelSoldierType value set in Tiled
	int nOfEnemy; // max enemies this spawner creates
		RebelSoldierPresets rsPreset; // behaviour presets for each soldier type

	static const int SPAWNRANGE = 300; // px, horizontal distance to the player
};
