#include "precomp.h"
#include "Helicopter.h"

#include <RigidBody.h>
#include <ResourceIDFrames.h>
#include <Renderer.h>
#include <BulletType.h>
#include <Bullets/Missle.h>
#include <myMath.h>

// DONE: change y position based on direction to give feel, make it spawn higher
Helicopter::Helicopter(vec2 pos) :
    Enemy(pos, EntityType::ET_HELICOPTER),
	elapsedTime(0.f),
	bulletsCount(0),
	bulletSpeed(0.2f),
	bullets{nullptr},
	startY(pos.y),
	maxY(pos.y + 25.f),
	shootOffset(40,20),
	lives(10) 
	{
    setCollider(vec2(100, 50), vec2(3, 0));
	getAnimationSets() = new AnimationSet[HelicopterAnimationSet::HAS_COUNTS];
	loadGFX();
	setCurrentASIndex(HelicopterAnimationSet::HAS_MOVE_FWD);

	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.03f);
}

Helicopter::~Helicopter(){
	delete[] getAnimationSets();
	for (int i = 0; i < MAXBULLETS; i++) {
		delete bullets[i];
		bullets[i] = nullptr;
	}
}

void Helicopter::loadGFX(){
	getAnimationSets()[HelicopterAnimationSet::HAS_MOVE_FWD] = AnimationSet(
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
			vec2(0, -4),
			vec2(0, 0))
	);
	getAnimationSets()[HelicopterAnimationSet::HAS_MOVE_BWD] = AnimationSet(
		2,
		AnimationLayer(
			ResourceID::ID_HELICOPTER_MOVE_BWD,
			ResourceIDFrames::IDF_HELICOPTER_MOVE_BWD,	
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
	getAnimationSets()[HelicopterAnimationSet::HAS_TRANSITION_FWD] = AnimationSet(
		2,
		AnimationLayer(
			ResourceID::ID_HELICOPTER_TRANSITION_FWD,
			ResourceIDFrames::IDF_HELICOPTER_TRANSITION_FWD,	
			200,
			vec2(0, -10),
			vec2(0, -10)),
		AnimationLayer(
			ResourceID::ID_HELICOPTER_BLADE,
			ResourceIDFrames::IDF_HELICOPTER_BLADE,
			100,
			vec2(0, -4),
			vec2(0, 0))
	);
	getAnimationSets()[HelicopterAnimationSet::HAS_TRANSITION_BWD] = AnimationSet(
		2,
		AnimationLayer(
			ResourceID::ID_HELICOPTER_TRANSITION_BWD,
			ResourceIDFrames::IDF_HELICOPTER_TRANSITION_BWD,	
			200,
			vec2(0, -10),
			vec2(0, -10)),
		AnimationLayer(
			ResourceID::ID_HELICOPTER_BLADE,
			ResourceIDFrames::IDF_HELICOPTER_BLADE,
			100,
			vec2(0, 0),
			vec2(0, 0))
	);
	getAnimationSets()[HelicopterAnimationSet::HAS_BOOM] = AnimationSet(
		1,
		AnimationLayer(
			ResourceID::ID_HELICOPTER_BOOM,
			ResourceIDFrames::IDF_HELICOPTER_BOOM,	
			200,
			vec2(0, -10),
			vec2(0, -10))
	);
}

void Helicopter::update(float dt) {
	clearSounds();
	getAnimator().playAnimation(dt);
	setColliderSprite();

	elapsedTime += dt;

	// Fly toward the player: distToPlayer > 0 means the player is to the left.
	float dirX = getSensors().distToPlayer > 0 ? -1.f : 1.f;
	//mini state machine
	{
		//DONE: if dist < xValue dont change animation
		int c = getCurrentASIndex(); // remember the animation, to restore it if the player is very close

		// Turning around plays a transition clip; turning back in the middle of it jumps straight to the move clip.
		if(getCurrentASIndex() == HAS_MOVE_FWD && dirX > 0){
			setCurrentASIndex(HAS_TRANSITION_BWD);
		}

		if(getCurrentASIndex() == HAS_TRANSITION_BWD){
			if(getAnimator().isAnimationEnded()){
				setCurrentASIndex(HAS_MOVE_BWD);
			}
			if(dirX < 0){
				setCurrentASIndex(HAS_MOVE_FWD);
			}
		}
		
		if(getCurrentASIndex() == HAS_MOVE_BWD && dirX < 0){
			setCurrentASIndex(HAS_TRANSITION_FWD);
		}

		if(getCurrentASIndex() == HAS_TRANSITION_FWD){
			if(getAnimator().isAnimationEnded()){
				setCurrentASIndex(HAS_MOVE_FWD);
			}
			if(dirX > 0){
				setCurrentASIndex(HAS_MOVE_BWD);
			}
		}

		// Right above the player: keep the previous animation (avoids flickering between directions).
		if(abs(getSensors().distToPlayer) < MINDIST){
			setCurrentASIndex(c);
		}

		// Out of lives: explode (only once).
		if(lives < 0 && getAlive()){
			setCurrentASIndex(HAS_BOOM);
			addSound(SoundID::SID_HELI_EXPLODING);
			setAlive(false);
		}	
		
		getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
	}

	if(getCurrentASIndex() == HAS_BOOM && getAnimator().isAnimationEnded()){
		setFree(true);
	}

	// The missiles keep flying even after the helicopter is destroyed.
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		bullets[i]->update(dt);
	}

	if(!getAlive()) return;

	// Move toward the player and bob: flying right it rises, flying left it sinks (kept between startY and maxY).
	setDir(vec2(dirX, 0));

	getRigidBody()->setVelocityX(getRigidBody()->getSpeed() * getDir().x);

	addToPos(getRigidBody()->getVelocity() * dt);

	if(dirX > 0){
		addToPos(vec2(0, -getRigidBody()->getSpeed() * dt));
	}else{
		addToPos(vec2(0, getRigidBody()->getSpeed() * dt));
	}

	setPos(vec2(getPos().x,
			myMath::constrain(getPos().y, startY, maxY)
		));


	// A volley = 3 missiles at once.
	if(elapsedTime > SHOOTCOOLDOWN){
		shoot();
		shoot();
		shoot();
		elapsedTime = 0.f;
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


	bullets[bIndex] = new Missle(getPos() + shootOffset + vec2(Rand(30.f) - 15.f, 0), true, vec2(0,1), BulletType::BT_MISSLE,bulletSpeed * myMath::mapValue(Rand(100.f),0.f, 100.f,0.6f,1.2f)); // random x spread of +-15 px, falls straight down at 60% .. 120% of bulletSpeed
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

void Helicopter::takeHit(){
	this->lives--;
}
