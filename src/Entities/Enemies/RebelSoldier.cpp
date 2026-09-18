#include "precomp.h"
#include <Enemies/RebelSoldier.h>
#include <RigidBody.h>

RebelSoldier::RebelSoldier(vec2 pos) :
	Enemy(pos)
{
	setCollider(vec2(20, 37), vec2(3, 0));
	//setCollider(vec2(20, 7), vec2(3, 30));
	getAnimationSets() = new AnimationSet[6];
	loadGFX();
	setCurrentASIndex(0);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
}

RebelSoldier::~RebelSoldier() {
	delete[] getAnimationSets();
}

void RebelSoldier::loadGFX() {

}

void RebelSoldier::update(float dt) {

	const bool isGrounded = getRigidBody()->isGrounded();
	getRigidBody()->setVelocityX(0.1f * getDir().x);

	if (!isGrounded) {
		getRigidBody()->addVelocity(vec2(0, 0.001f * dt));
	}
	else {
		getRigidBody()->setVelocityY(0);
	}


	this->addToPos(getRigidBody()->getVelocity() * dt);

}