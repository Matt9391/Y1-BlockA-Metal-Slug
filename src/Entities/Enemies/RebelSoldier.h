#pragma once
#include <Enemy.h>
#include <EnemyState.h>


class RebelSoldier : public Enemy {
public:
	RebelSoldier(vec2 pos);
	~RebelSoldier() override;

	void loadGFX() override;

	void update(float dt) override;

private:
	RebelSoldierStates::EnemyState* state;
	
};
