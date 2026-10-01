#include "precomp.h"
#include "GunPresets.h"

GunData GunPresets::gunPresets[GunType::COUNTS] = {
	GunData(BulletType::BT_PISTOL, 100, false, 0.5f) //PISTOL
};


const GunData& GunPresets::getGun(GunType gunType) {
	return gunPresets[gunType];
}