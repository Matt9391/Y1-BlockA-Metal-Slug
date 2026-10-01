#pragma once
#include <BulletType.h>
#include <GunType.h>


struct GunData {

	GunData() :
		gunType(GunType::PISTOL),
		bulletType(BulletType::BT_COUNTS),
		fireRate(-1),
		canShootDiagonally(false),
		bulletSpeed(0.f)
	{}

	GunData(GunType gunType, BulletType bulletType, float fireRate, bool canShootDiagonally, float bulletSpeed) :
		gunType(gunType),
		bulletType(bulletType),
		fireRate(fireRate),
		canShootDiagonally(canShootDiagonally),
		bulletSpeed(bulletSpeed)
	{}

	GunType gunType;
	BulletType bulletType;
	float fireRate; //time between shots
	float bulletSpeed;
	bool canShootDiagonally;
};