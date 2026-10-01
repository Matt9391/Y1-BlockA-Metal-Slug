#include "precomp.h"
#include "GunPresets.h"

GunData GunPresets::gunPresets[GunType::COUNTS] = {
	GunData(GunType::PISTOL ,BulletType::BT_PISTOL, 100, false, 0.5f), //PISTOL
	GunData(GunType::FLAME_THROWER ,BulletType::BT_FLAME_THROWER, 400, true, 0.2f)
};


const GunData& GunPresets::getGun(GunType gunType) {
	return gunPresets[gunType];
}