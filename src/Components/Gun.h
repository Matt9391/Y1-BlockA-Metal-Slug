#pragma once
#include <vec2.h>
#include <GunData.h>

enum ResourceId;
class Bullet;

class Gun {

public:
	Gun(vec2 pos, GunData gunData);

	void update(float dt);

private:
	vec2 pos;
	vec2 shootDir;
	GunData gunData;
	Bullet* bullets;
};