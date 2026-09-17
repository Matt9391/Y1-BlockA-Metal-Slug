#pragma once
#include <Enemy.h>

class RebelSoldier : public Enemy {
public:
	RebelSoldier(vec2 pos);
	~RebelSoldier() override;

	void loadGFX() override;

private:


};
