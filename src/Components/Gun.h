#pragma once
#include <vec2.h>
#include <GunData.h>

class Bullet;
struct RenderData;
class Renderer;

class Gun {

public:
	Gun(const vec2& pos, vec2 offset, GunData gunData);
	~Gun();
	void update(float dt);

	void addRenderDatas(Renderer& renderer);
	int getBulletsCount() const;
	int getMaxBullets() const;
	Bullet* getBullet(int i) const;

	void freeBullet(int i);
	bool getCanShootDiagonally() const;

	void setShootDir(vec2 shootDir_);
	bool shoot();
	bool getCanShoot() const;

	void setOffsetX(float offsetX);
	void setOffsetY(float offsetY);
	void setOffset(vec2 offset_);

	void setGunData(GunData newData);
	GunType getGunType() const;

	void setGunAngle(float gunAngle_);

private:
	static const int MAXBULLETS = 50;

	const vec2& pos;
	vec2 offset;
	vec2 shootDir;
	GunData gunData;
	Bullet* bullets[MAXBULLETS];
	int bulletsCount;
	bool canShoot;
	float shootCooldown;
	float gunAngle;
};