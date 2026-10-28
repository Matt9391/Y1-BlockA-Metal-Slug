#pragma once
#include <Enemy.h>
#include <EnemyState.h>
#include <Granade.h>
#include <RebelSoldierPresets.h>

class Renderer;

// RebelSoldier - the basic enemy. Its behaviour (wander, take cover, knife, grenades, get scared...) lives in
// RebelSoldierStates (EnemyState.cpp); which attacks it is allowed to use comes from its RebelSoldierData.
class RebelSoldier : public Enemy {
public:
	RebelSoldier(vec2 pos,const RebelSoldierData& rsData);
	~RebelSoldier() override;

	void loadGFX() override;

	void update(float dt) override;

	bool throwGranade(vec2 dir_); // spawn a grenade flying in direction dir_ (false if the pool is full)

	void addRenderDatas(Renderer& renderer); // draw its grenades 

	void freeGranade(int i);
	Granade* getGranade(int i) const;

	int getMaxGranades() const;
	const RebelSoldierData& getData() const;

private:
	RebelSoldierStates::EnemyState* state; // current state object (shared by all soldiers, see EnemyState.h)
	
	static const int MAXGRANADES = 5;

	Granade* granades[MAXGRANADES]; // fixed pool, nullptr = free slot
	int granadesCount;

	float deathTimeElapsed; // ms the corpse has been lying there
	const float DEATHTIMER = 500.f; // ms before the corpse is removed
	RebelSoldierData rsData; // which attacks this soldier can use
};

