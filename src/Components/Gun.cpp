#include "precomp.h"
#include "Gun.h"
#include <Bullet.h>
#include <RenderSet.h>
#include <Renderer.h>
#include <GunType.h>

Gun::Gun(const vec2& pos, vec2 offset, GunData gunData) :
	pos(pos),
	offset(offset),
	gunData(gunData),
	shootDir(0,0),
	bullets{},
	bulletsCount(0),
	canShoot(true),
	shootCooldown(0.f)
{}

Gun::~Gun() {

	for (int i = 0; i < MAXBULLETS; i++) {
		delete bullets[i];
		bullets[i] = nullptr;
	}
}

void Gun::update(float dt) {
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		bullets[i]->update(dt);
	}

	if(!canShoot){
		shootCooldown += dt;
		if(shootCooldown > gunData.fireRate){
			shootCooldown = 0.f;
			canShoot = true;
		}
	}
}

bool Gun::shoot() {
	if(!canShoot) return false;

	int bIndex = -1;
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;

	bullets[bIndex] = new Bullet(this->pos + this->offset, true, this->shootDir, gunData.bulletType, gunData.bulletSpeed);
	bulletsCount++;

	canShoot = false;

	return true;
}

bool Gun::getCanShoot() const {
	return this->canShoot;
}


void Gun::addRenderSets(Renderer& renderer) {
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		renderer.addRenderSet(bullets[i]->getRenderSet());
		renderer.addCollider(bullets[i]->getCollider());

	}
}

int Gun::getBulletsCount() {
	return bulletsCount;
}

Bullet* Gun::getBullet(int i) {
	return bullets[i];
}

void Gun::freeBullet(int i) {
	if (bullets[i]) {
		delete bullets[i];
		bullets[i] = nullptr;
		bulletsCount--;
	}
}

int Gun::getMaxBullets() const{
	return MAXBULLETS;
}

bool Gun::getCanShootDiagonally() {
	return gunData.canShootDiagonally;
}

void Gun::setShootDir(vec2 shootDir) {
	this->shootDir = shootDir;
}

void Gun::setOffset(vec2 offset) {
	this->offset = offset;
}

void Gun::setOffsetY(float offsetY) {
	this->offset.y = offsetY;
}

void Gun::setOffsetX(float offsetX) {
	this->offset.x = offsetX;
}

void Gun::setGunData(GunData newData) {

	this->gunData = newData;

}

GunType Gun::getGunType() const{
	return this->gunData.gunType;
}