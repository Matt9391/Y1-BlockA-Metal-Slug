#pragma once
#include <BulletType.h>


struct GunData {

	GunData() :
		bulletType(BulletType::BT_COUNTS),
		fireRate(-1),
		canShootDiagonally(false),
		bulletSpeed(0.f)
	{}

	GunData(BulletType bulletType, float fireRate, bool canShootDiagonally, float bulletSpeed) :
		bulletType(bulletType),
		fireRate(fireRate),
		canShootDiagonally(canShootDiagonally),
		bulletSpeed(bulletSpeed)
	{}

	BulletType bulletType;
	float fireRate; //time between shots
	float bulletSpeed;
	bool canShootDiagonally;
};