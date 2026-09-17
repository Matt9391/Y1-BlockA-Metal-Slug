#pragma once
#include <GunData.h>
#include <GunType.h>

class GunPresets {

public:
	static const GunData& getGun(GunType gunType);

private:
	static GunData gunPresets[GunType::COUNTS];
};