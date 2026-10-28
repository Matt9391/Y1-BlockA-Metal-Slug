#pragma once
#include <vec2.h>
#include <GunData.h>

class Bullet;
struct RenderData;
class Renderer;

class Gun {

public:
	Gun(const vec2& pos, vec2 offset, GunData gunData); // pos is a reference to the owner's position
	~Gun();
	void update(float dt);

	void addRenderDatas(Renderer& renderer);
	int getBulletsCount() const;
	int getMaxShootBullet() const;
	int getMaxBullets() const;
	Bullet* getBullet(int i) const;

	void freeBullet(int i); // delete bullet i and free its slot in the pool
	bool getCanShootDiagonally() const;

	void setShootDir(vec2 shootDir_);
	bool shoot(); // spawn a bullet if the cooldown allows it; returns true on success
	bool getCanShoot() const;
	int getBulletShot() const; // shots fired since the last resetBulletShot() (used for limited ammo)

	void setOffsetX(float offsetX);
	void setOffsetY(float offsetY);
	void setOffset(vec2 offset_);

	void setGunData(GunData newData);
	GunType getGunType() const;

	void setGunAngle(float gunAngle_); // aim angle in degrees (0 = forward, 90 = straight up), used by the flame thrower

	void resetBulletShot();

	float getStandOffsetY()  const;
	float getCrouchOffsetY() const;
	float getLookUpOffsetY() const;

private:
	static const int MAXBULLETS = 50;

	const vec2& pos; // owner's position (reference)
	vec2 offset; // bullet spawn point relative to pos
	vec2 shootDir;
	GunData gunData;
	Bullet* bullets[MAXBULLETS]; // fixed pool, nullptr = free slot
	int bulletsCount;
	int bulletShot;
	bool canShoot; // false while the fire-rate cooldown is running
	float shootCooldown; // time since the last shot, in ms
	float gunAngle;
};