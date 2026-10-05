#pragma once
#include <Enemy.h>
#include <EnemyState.h>
#include <Granade.h>
#include <RebelSoldierPresets.h>

class Renderer;

class RebelSoldier : public Enemy {
public:
	RebelSoldier(vec2 pos,const RebelSoldierData& rsData);
	~RebelSoldier() override;

	void loadGFX() override;

	void update(float dt) override;

	bool throwGranade(vec2 dir_);

	void addRenderSets(Renderer& renderer);

	void freeGranade(int i);
	Granade* getGranade(int i) const;

	int getMaxGranades() const;
	const RebelSoldierData& getData() const;

private:
	RebelSoldierStates::EnemyState* state;
	
	static const int MAXGRANADES = 5;

	Granade* granades[MAXGRANADES];
	int granadesCount;

	float deathTimeElapsed;
	const float DEATHTIMER = 500.f;
	RebelSoldierData rsData;
};
