#include "precomp.h"
#include "Granade.h"
#include <ResourceIDFrames.h>

Granade::Granade(vec2 pos, bool needsRigidBody, vec2 dir) :
	Entity(pos, needsRigidBody),
	arcWidth(50.f),
	startPos(pos),
	duration(800.f), //ms
	elapsedTime(0.f),
	peakHeight(150.f)
{
	setCollider(vec2(5, 5), vec2(0, 0));
	getAnimationSets() = new AnimationSet[1];
	loadGFX();
	setCurrentASIndex(0);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	setDir(dir);
}

Granade::~Granade() {
	delete[] getAnimationSets();
}

void Granade::loadGFX() {
	getAnimationSets()[0] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_FALLING_LEGS,
			ResourceIDFrames::IDF_PLAYER_FALLING_LEGS,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
}

void Granade::update(float dt) {
	getAnimator().playAnimation(dt);

	// y = 1 - (2x - 1)^2
	elapsedTime += dt;

	float x = elapsedTime / duration;
	float y = 1.f - powf((2.f * x - 1.f), 2.f);

	float worldX = startPos.x + arcWidth * x * getDir().x;
	float worldY = startPos.y - peakHeight * y;

	setPos(vec2(worldX, worldY));
}