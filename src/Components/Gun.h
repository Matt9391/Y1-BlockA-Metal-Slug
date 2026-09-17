#pragma once
#include <vec2.h>
#include <GunData.h>

enum ResourceId;
class Bullet;
struct RenderSet;
class Renderer;

class Gun {

public:
	Gun(const vec2& pos, vec2 offset, GunData gunData);
	~Gun();
	void update(float dt);

	void addRenderSets(Renderer& renderer);
	int getBulletsCount();

	bool shoot();

private:
	static const int MAXBULLETS = 10;

	const vec2& pos;
	vec2 offset;
	vec2 shootDir;
	GunData gunData;
	Bullet* bullets[MAXBULLETS];
	int bulletsCount;
};