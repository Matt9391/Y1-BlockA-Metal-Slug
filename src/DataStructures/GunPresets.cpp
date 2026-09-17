#include "precomp.h"
#include "GunPresets.h"

GunData GunPresets::gunPresets[GunType::COUNTS] = {
	GunData(ResourceID::ID_BULLET_PISTOL, 100, false) //PISTOL
};


const GunData& GunPresets::getGun(GunType gunType) {
	return gunPresets[gunType];
}