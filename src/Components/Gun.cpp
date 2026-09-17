#include "precomp.h"
#include "Gun.h"
#include <Bullet.h>
#include <RenderSet.h>
#include <Renderer.h>

Gun::Gun(const vec2& pos, vec2 offset, GunData gunData) :
	pos(pos),
	offset(offset),
	gunData(gunData),
	shootDir(0,0),
	bullets{},
	bulletsCount(0)
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
}

bool Gun::shoot() {
	int bIndex = -1;
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;

	bullets[bIndex] = new Bullet(this->pos, true);
	bulletsCount++;

	return true;
}

void Gun::addRenderSets(Renderer& renderer) {
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		renderer.addRenderSet(bullets[i]->getRenderSet());
	}
}

int Gun::getBulletsCount() {
	return bulletsCount;
}