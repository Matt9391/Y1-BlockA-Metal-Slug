#pragma once
#include <RebelSoldierType.h>


struct RebelSoldierData {
	bool canAttackMelee;
	bool canAttackGranade;
};

class RebelSoldierPresets {

public:
	RebelSoldierPresets();

	const RebelSoldierData& getRebelSoliderPreset(RebelSoldierType rebelSoldierType) const;

private:
	RebelSoldierData presets[RebelSoldierType::RST_COUNTS];
};