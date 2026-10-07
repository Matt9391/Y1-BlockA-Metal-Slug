#include "precomp.h"
#include "Helicopter.h"

#include <RigidBody.h>
#include <ResourceIDFrames.h>
#include <Renderer.h>
#include <BulletType.h>
#include <Bullets/Missle.h>

Helicopter::Helicopter(vec2 pos) :
    Enemy(pos, EntityType::ET_HELICOPTER),
	elapsedTime(0.f),
	bulletsCount(0),
	bulletSpeed(0.5f),
	bullets{nullptr}
{
    setCollider(vec2(50, 37), vec2(3, 0));
	getAnimationSets() = new AnimationSet[HelicopterAnimationSet::HAS_COUNTS];
	loadGFX();
	setCurrentASIndex(HelicopterAnimationSet::HAS_MOVE);

	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.1f);
}

Helicopter::~Helicopter(){
	delete[] getAnimationSets();
}

void Helicopter::loadGFX(){
	getAnimationSets()[HelicopterAnimationSet::HAS_MOVE] = AnimationSet(
		2,
		AnimationLayer(
			ResourceID::ID_HELICOPTER_MOVE,
			ResourceIDFrames::IDF_HELICOPTER_MOVE,	
			100,
			vec2(0, 0),
			vec2(0, 0)),
		AnimationLayer(
			ResourceID::ID_HELICOPTER_BLADE,
			ResourceIDFrames::IDF_HELICOPTER_BLADE,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
}

void Helicopter::update(float dt) {
	getAnimator().playAnimation(dt);

	elapsedTime += dt;

	float dirX = getSensors().distToPlayer > 0 ? -1.f : 1.f;

	setDir(vec2(dirX, 0));

	getRigidBody()->setVelocityX(getRigidBody()->getSpeed() * getDir().x);
	printf("x: %.2f, y: %.2f\n", getPos().x, getPos().y);

	addToPos(getRigidBody()->getVelocity() * dt);

	if(elapsedTime > SHOOTCOOLDOWN){
		shoot();
		elapsedTime = 0.f;
	}

	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		bullets[i]->update(dt);
	}

}


bool Helicopter::shoot() {

	int bIndex = -1;
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;


	bullets[bIndex] = new Missle(getPos(), true, vec2(0,1), BulletType::BT_MISSLE,bulletSpeed);
	bulletsCount++;

	return true;
}

void Helicopter::freeBullet(int i) {
	if (bullets[i]) {
		delete bullets[i];
		bullets[i] = nullptr;
		bulletsCount--;
	}
}

void Helicopter::addRenderDatas(Renderer& renderer) {
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		renderer.addRenderData(bullets[i]->getRenderData());
		renderer.addCollider(bullets[i]->getCollider());

	}
}

int Helicopter::getMaxBullets() const{
	return MAXBULLETS;
}

Bullet* Helicopter::getBullet(int i) const {
	return bullets[i];
}
