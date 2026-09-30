#include "precomp.h"
#include "RebelSoldierPresets.h"

RebelSoldierPresets::RebelSoldierPresets() :
	presets{
		RebelSoldierData{false, false}, //nothing
		RebelSoldierData{true, false}, //melee
		RebelSoldierData{true, true}, //melee & grenade
	}
{}

const RebelSoldierData& RebelSoldierPresets::getRebelSoliderPreset(RebelSoldierType rebelSoldierType) const {
	return presets[rebelSoldierType];
}