#include "precomp.h"
#include "Tank.h"
#include <TankAnimationSet.h>
#include <RigidBody.h>
#include <ResourceIDFrames.h>
#include <Player.h>



Tank::Tank(vec2 pos, const InputManager& inputManager_) :
    Entity(pos, true, EntityType::ET_TANK),
    inputManager(inputManager_),
    player(nullptr),
    gotHit(false),
    dead(false)
{
    setCollider(vec2(40, 20), vec2(3, 0));
	//setCollider(vec2(20, 7), vec2(3, 30));
	getAnimationSets() = new AnimationSet[TankAnimationSet::TAS_COUNTS];
	loadGFX();
	setCurrentASIndex(TankAnimationSet::TAS_IDLE);
	state = TankStates::getTankState(static_cast<TankAnimationSet>(getCurrentASIndex()));
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.05f);

}

Tank::~Tank(){
	delete[] getAnimationSets();
}

void Tank::loadGFX() {
    // TAS_IDLE -> idle.png
    getAnimationSets()[TankAnimationSet::TAS_IDLE] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_IDLE,
            ResourceIDFrames::IDF_TANK_IDLE,
            150,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_WALK -> walk.png
    getAnimationSets()[TankAnimationSet::TAS_WALK] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_WALK,
            ResourceIDFrames::IDF_TANK_WALK,
            100,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_SHOOT -> shoot.png
    getAnimationSets()[TankAnimationSet::TAS_SHOOT] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_SHOOT,
            ResourceIDFrames::IDF_TANK_SHOOT,
            50,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_EXPLOSION -> hit.png
    getAnimationSets()[TankAnimationSet::TAS_EXPLOSION] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_EXPLOSION,
            ResourceIDFrames::IDF_TANK_EXPLOSION,
            100,
            vec2(0, 0),
            vec2(0, 0))
    );
 
    // TAS_EXPLOSION_STILL -> hit_still.png (single frame, still to be created)
    getAnimationSets()[TankAnimationSet::TAS_EXPLOSION_STILL] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_EXPLOSION_STILL,
            ResourceIDFrames::IDF_TANK_EXPLOSION_STILL,
            100,
            vec2(0, 0),
            vec2(0, 0))
    );
}

void Tank::update(float dt){
    getAnimator().playAnimation(dt);

    if (!getRigidBody()->isGrounded()) {
		addVelocity(vec2(0, getRigidBody()->getGravity() * dt));
	}
	else {
		setVelocityY(0.f);
	}

    if(this->player == nullptr);
    return;
    //SKIP IF NOT OWN

    

}

const TankStates::TankInput Tank::getTankInput() const {
	const bool inputRight = inputManager.isKeyPressed('D');
	const bool inputLeft = inputManager.isKeyPressed('A');
	const bool isMoving = inputRight || inputLeft;
	const bool isGrounded = getRigidBody()->isGrounded();
	const bool isShooting = inputManager.isKeyJustPressed('F');
	const bool isHit = gotHit;
	const bool isDead = dead;

	const TankStates::TankInput tankInput = {
		inputRight,
		inputLeft,
		isMoving,
		isGrounded,
		isShooting,
		getAnimator().isAnimationEnded(),
		isHit,
        isDead
	};

	return tankInput;
}


void Tank::enterPlayer(const Player* player_){
    this->player = player_;
}