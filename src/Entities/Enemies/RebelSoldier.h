#pragma once
#include <Enemy.h>
#include <EnemyState.h>
#include <Granade.h>

class Renderer;

class RebelSoldier : public Enemy {
public:
	RebelSoldier(vec2 pos);
	~RebelSoldier() override;

	void loadGFX() override;

	void update(float dt) override;

	bool throwGranade(vec2 dir);

	void addRenderSets(Renderer& renderer);

	void freeGranade(int i);

private:
	RebelSoldierStates::EnemyState* state;
	
	Granade* granades[10];
	int granadesCount;
};
