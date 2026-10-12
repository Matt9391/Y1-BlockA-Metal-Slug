#include "precomp.h"
#include "Boss.h"


#include <RigidBody.h>
#include <ResourceIDFrames.h>
#include <Renderer.h>
#include <BulletType.h>
#include <Bullets/Missle.h>
#include <myMath.h>

// DONE: change y position based on direction to give feel, make it spawn higher
Boss::Boss(vec2 pos) :
    Enemy(pos, EntityType::ET_BOSS)
	{
    setCollider(vec2(100, 50), vec2(3, 0));
	getAnimationSets() = new AnimationSet[1];
	loadGFX();
	setCurrentASIndex(0);

	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.03f);
}

Boss::~Boss(){
	delete[] getAnimationSets();
}

void Boss::loadGFX(){
	getAnimationSets()[0] = AnimationSet(
		2,
		AnimationLayer(
			ResourceID::ID_HELICOPTER_MOVE_FWD,
			ResourceIDFrames::IDF_HELICOPTER_MOVE_FWD,	
			100,
			vec2(0, -10),
			vec2(0, -10)),
		AnimationLayer(
			ResourceID::ID_HELICOPTER_BLADE,
			ResourceIDFrames::IDF_HELICOPTER_BLADE,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
}

void Boss::update(float dt) {
	getAnimator().playAnimation(dt);

	float dirX = getSensors().distToPlayer > 0 ? -1.f : 1.f;

    getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);


	// for (int i = 0; i < MAXBULLETS; i++) {
	// 	if (bullets[i] == nullptr) continue;
	// 	bullets[i]->update(dt);
	// }

}


// bool Boss::shoot() {

// 	int bIndex = -1;
// 	for (int i = 0; i < MAXBULLETS; i++) {
// 		if (bullets[i] == nullptr) {
// 			bIndex = i;
// 			break;
// 		}
// 	}

// 	if (bIndex == -1) return false;


// 	bullets[bIndex] = new Missle(getPos() + shootOffset + vec2(Rand(30.f) - 15.f, 0), true, vec2(0,1), BulletType::BT_MISSLE,bulletSpeed * myMath::mapValue(Rand(100.f),0.f, 100.f,0.6f,1.2f));
// 	bulletsCount++;

// 	return true;
// }

// void Boss::freeBullet(int i) {
// 	if (bullets[i]) {
// 		delete bullets[i];
// 		bullets[i] = nullptr;
// 		bulletsCount--;
// 	}
// }

// void Boss::addRenderDatas(Renderer& renderer) {
// 	for (int i = 0; i < MAXBULLETS; i++) {
// 		if (bullets[i] == nullptr) continue;
// 		renderer.addRenderData(bullets[i]->getRenderData());
// 		renderer.addCollider(bullets[i]->getCollider());

// 	}
// }

// int Boss::getMaxBullets() const{
// 	return MAXBULLETS;
// }

// Bullet* Boss::getBullet(int i) const {
// 	return bullets[i];
// }

// void Boss::takeHit(){
// 	this->lives--;
// }
