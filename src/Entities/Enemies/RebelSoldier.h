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
	Granade* getGranade(int i);

	int getMaxGranades() const;

private:
	RebelSoldierStates::EnemyState* state;
	
	static const int MAXGRANADES = 5;

	Granade* granades[MAXGRANADES];
	int granadesCount;
};
