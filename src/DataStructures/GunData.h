#pragma once

enum ResourceId;

struct GunData {
	bool canShootDiagonally;
	float fireRate; //time between shots
	ResourceId resourceId;
};