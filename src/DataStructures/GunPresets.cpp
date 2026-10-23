#include "precomp.h"
#include "GunPresets.h"

GunData GunPresets::gunPresets[GunType::COUNTS] = {
	GunData(GunType::PISTOL ,BulletType::BT_PISTOL, 100, false, 0.5f,-1, 5.f, 20.f, 5.f), //PISTOL
	GunData(GunType::FLAME_THROWER ,BulletType::BT_FLAME_THROWER, 400, true, 0.3f,20, 5.f, 8.f, -15.f)
};


const GunData& GunPresets::getGun(GunType gunType) {
	return gunPresets[gunType];
}