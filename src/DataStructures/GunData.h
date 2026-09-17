#pragma once
#include <ResourceID.h>


struct GunData {

	GunData() :
		bulletResourceId(ResourceID::ID_NULL),
		fireRate(-1),
		canShootDiagonally(false)
	{}

	GunData(ResourceID bulletResourceId, float fireRate, bool canShootDiagonally) :
		bulletResourceId(bulletResourceId),
		fireRate(fireRate),
		canShootDiagonally(canShootDiagonally)
	{}

	ResourceID bulletResourceId;
	float fireRate; //time between shots
	bool canShootDiagonally;
};