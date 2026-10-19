#pragma once
#include <BulletType.h>
#include <GunType.h>


struct GunData {

	GunData() :
		gunType(GunType::PISTOL),
		bulletType(BulletType::BT_COUNTS),
		fireRate(-1),
		canShootDiagonally(false),
		bulletSpeed(0.f),
		maxShootBullet(0)
	{}

	GunData(GunType gunType, BulletType bulletType, float fireRate, bool canShootDiagonally, float bulletSpeed, int maxShootBullet) :
		gunType(gunType),
		bulletType(bulletType),
		fireRate(fireRate),
		canShootDiagonally(canShootDiagonally),
		bulletSpeed(bulletSpeed),
		maxShootBullet(maxShootBullet)
	{}

	GunType gunType;
	BulletType bulletType;
	float fireRate; //time between shots
	float bulletSpeed;
	bool canShootDiagonally;
	int maxShootBullet;
};