#include "precomp.h"
#include "Boss.h"


#include <RigidBody.h>
#include <BossAnimationSet.h>
#include <ResourceIDFrames.h>
#include <Renderer.h>
#include <BulletType.h>
#include <Bullets/CannonBall.h>
#include <Bullets/LaserBall.h>
#include <myMath.h>

// DONE: change y position based on direction to give feel, make it spawn higher
Boss::Boss(vec2 pos) :
    Enemy(pos, EntityType::ET_BOSS),
	shootOffset{-2,10},
    bulletsCount(0),
	bulletSpeed(0.1f),
	bullets{nullptr},
    life(100)
	{
    setCollider(vec2(10, 105), vec2(0,0));
	getAnimationSets() = new AnimationSet[BossAnimationSet::BAS_COUNTS];
	loadGFX();
	setCurrentASIndex(BossAnimationSet::BAS_ATTACK_ONE_HIGH);
	state = BossStates::getBossState(BossAnimationSet::BAS_ATTACK_ONE_HIGH);
	state->enter(*this);

	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.07f);//SPEED OF CANNON MOVEMENT UP/DOWN
}

Boss::~Boss(){
	delete[] getAnimationSets();
}
void Boss::loadGFX() {
    // BAS_ATTACK_ONE_HIGH -> cannon fire, high (cannon_fire_high.png)
    getAnimationSets()[BossAnimationSet::BAS_ATTACK_ONE_HIGH] = AnimationSet(
        2,
        AnimationLayer(
            ResourceID::ID_BOSS_BODY,
            ResourceIDFrames::IDF_BOSS_BODY,
            100,
            vec2(-265, -100),
            vec2(0, 0)),
        AnimationLayer(
            ResourceID::ID_BOSS_CANNON_FIRE_HIGH,
            ResourceIDFrames::IDF_BOSS_CANNON_FIRE_HIGH,
            50,
            vec2(-36, 31),
            vec2(0, 0))
    );
 
    // BAS_ATTACK_ONE_LOW -> cannon fire, low (cannon_fire_low.png)
    getAnimationSets()[BossAnimationSet::BAS_ATTACK_ONE_LOW] = AnimationSet(
        2,
        AnimationLayer(
            ResourceID::ID_BOSS_BODY,
            ResourceIDFrames::IDF_BOSS_BODY,
            100,
            vec2(-265, -100),
            vec2(0, 0)),
        AnimationLayer(
            ResourceID::ID_BOSS_CANNON_FIRE_LOW,
            ResourceIDFrames::IDF_BOSS_CANNON_FIRE_LOW,
            50,
            vec2(-36, 31),
            vec2(0, 0))
    );
 
    // BAS_ATTACK_TWO_HIGH -> cannon laser, high (cannon_laser_high.png)
    getAnimationSets()[BossAnimationSet::BAS_ATTACK_TWO_HIGH] = AnimationSet(
        2,
        AnimationLayer(
            ResourceID::ID_BOSS_BODY,
            ResourceIDFrames::IDF_BOSS_BODY,
            100,
            vec2(-265, -100),
            vec2(0, 0)),
        AnimationLayer(
            ResourceID::ID_BOSS_CANNON_LASER_HIGH,
            ResourceIDFrames::IDF_BOSS_CANNON_LASER_HIGH,
            50,
            vec2(-36, 31),
            vec2(0, 0))
    );
 
    // BAS_ATTACK_TWO_LOW -> cannon laser, low (cannon_laser_low.png)
    getAnimationSets()[BossAnimationSet::BAS_ATTACK_TWO_LOW] = AnimationSet(
        2,
        AnimationLayer(
            ResourceID::ID_BOSS_BODY,
            ResourceIDFrames::IDF_BOSS_BODY,
            100,
            vec2(-265, -100),
            vec2(0, 0)),
        AnimationLayer(
            ResourceID::ID_BOSS_CANNON_LASER_LOW,
            ResourceIDFrames::IDF_BOSS_CANNON_LASER_LOW,
            50,
            vec2(-36, 31),
            vec2(0, 0))
    );
 
    // BAS_MOVE_UP -> cannon_moving_up.png
    getAnimationSets()[BossAnimationSet::BAS_MOVE_UP] = AnimationSet(
        2,
        AnimationLayer(
            ResourceID::ID_BOSS_BODY,
            ResourceIDFrames::IDF_BOSS_BODY,
            100,
            vec2(-265, -100),
            vec2(0, 0)),
        AnimationLayer(
            ResourceID::ID_BOSS_CANNON_MOVING_UP,
            ResourceIDFrames::IDF_BOSS_CANNON_MOVING_UP,
            25,
            vec2(-36, 31),
            vec2(0, 0))
    );
 
    // BAS_MOVE_DOWN -> cannon_moving_down.png
    getAnimationSets()[BossAnimationSet::BAS_MOVE_DOWN] = AnimationSet(
        2,
        AnimationLayer(
            ResourceID::ID_BOSS_BODY,
            ResourceIDFrames::IDF_BOSS_BODY,
            100,
            vec2(-265, -100),
            vec2(0, 0)),
        AnimationLayer(
            ResourceID::ID_BOSS_CANNON_MOVING_DOWN,
            ResourceIDFrames::IDF_BOSS_CANNON_MOVING_DOWN,
            25,
            vec2(-36, 31),
            vec2(0, 0))
    );
 
    // BAS_DEATH -> destroyed hull + destroyed cannon + explosion
    getAnimationSets()[BossAnimationSet::BAS_DEATH] = AnimationSet(
        2,
        AnimationLayer(
            ResourceID::ID_BOSS_EXPLOSION,
            ResourceIDFrames::IDF_BOSS_EXPLOSION,
            100,
            vec2(-265, -100),
            vec2(0, 0)),
        AnimationLayer(
            ResourceID::ID_BOSS_CANNON_DESTROYED,
            ResourceIDFrames::IDF_BOSS_CANNON_DESTROYED,
            50,
            vec2(-36, 31),
            vec2(0, 0))        
    );
}

void Boss::update(float dt) {
	getAnimator().playAnimation(dt);

	if (!getSensors().isGrounded) {
		addVelocity(vec2(0, getRigidBody()->getGravity() * dt));
	}
	else {
		setVelocityY(0.f);
	}

	BossAnimationSet nextState = state->update(*this, dt, static_cast<BossAnimationSet>(getCurrentASIndex()));
	if (nextState != getCurrentASIndex()) {
		setCurrentASIndex(nextState);
		state = BossStates::getBossState(static_cast<BossAnimationSet>(getCurrentASIndex()));
		state->enter(*this);

	}


	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], getFlip());


	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		bullets[i]->update(dt);
	}

}

void Boss::moveShootOffset(vec2 incr){
	this->shootOffset += incr;	
}

bool Boss::shootCannon() {
	int bIndex = -1;
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;


	bullets[bIndex] = new CannonBall(getPos() + getCollider().offset + shootOffset + vec2(Rand(30.f) - 15.f,0),
									true, 
									vec2(-1,0), 
									BulletType::BT_CANNON_BALL,
									Rand(150.f) + 1500.f,
                                    abs(getSensors().distToPlayer));
	bulletsCount++;

	return true;
}

bool Boss::shootLaserBall() {
	int bIndex = -1;
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) {
			bIndex = i;
			break;
		}
	}

	if (bIndex == -1) return false;


	bullets[bIndex] = new LaserBall(getPos() + getCollider().offset + shootOffset + vec2(0, 42),
									true, 
									vec2(-1,0), 
									BulletType::BT_LASER_BALL, 
                                    0.1f);
	bulletsCount++;

	return true;
}

void Boss::freeBullet(int i) {
	if (bullets[i]) {
		delete bullets[i];
		bullets[i] = nullptr;
		bulletsCount--;
	}
}

void Boss::addRenderDatas(Renderer& renderer) {
	for (int i = 0; i < MAXBULLETS; i++) {
		if (bullets[i] == nullptr) continue;
		renderer.addRenderData(bullets[i]->getRenderData());
		renderer.addCollider(bullets[i]->getCollider());

	}
}

int Boss::getMaxBullets() const{
	return MAXBULLETS;
}

Bullet* Boss::getBullet(int i) const {
	return bullets[i];
}

int Boss::getLife() const{
    return this->life;
}

// void Boss::takeHit(){
// 	this->lives--;
// }
