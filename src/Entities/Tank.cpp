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
    dead(false),
    hp(5)
{
    setCollider(vec2(60, 50), vec2(15, 10));
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
    
    getAnimationSets()[TankAnimationSet::TAS_HIT] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_TANK_HIT,
            ResourceIDFrames::IDF_TANK_HIT,
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
    
    RigidBody* rb = getRigidBody();

    if (!rb->isGrounded()) {
		addVelocity(vec2(0, rb->getGravity() * dt));
	}
	else {
		setVelocityY(0.f);
	}

    if(this->player == nullptr){
        rb->setVelocityX(0);
		setDir(vec2(0, 0));

    	this->addToPos(rb->getVelocity() * dt);
        
        return;

    }

    //SKIP IF NOT OWN

    player->setPos(getPos() + vec2(30,15));


    const TankStates::TankInput tInput = getTankInput();

    TankAnimationSet nextState = state->handleInput(tInput, static_cast<TankAnimationSet>(getCurrentASIndex()));
    setCurrentASIndex(nextState);
    state = TankStates::getTankState(static_cast<TankAnimationSet>(getCurrentASIndex()));


	if (getDir().x != 0)
		setLastDir(getDir());
	setDir(vec2(0, 0));

	//Movement
	if (tInput.inputRight) {
		setDir(vec2(1, 0));
	}
	else if (tInput.inputLeft) {
		setDir(vec2(-1, 0));
	}

	rb->setVelocityX(rb->getSpeed() * getDir().x);

	this->addToPos(rb->getVelocity() * dt);

    const bool flip = getLastDir().x < 0;
	const bool reset = tInput.isShooting && getCurrentASIndex() != TankAnimationSet::TAS_HIT && !tInput.isDead;

	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], flip, reset);

    //reset bools
    gotHit = false;
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


void Tank::enterPlayer(Player* player_){
    this->player = player_;
}


bool Tank::hasPlayer() const{
    return this->player != nullptr;
}

void Tank::takeHit(){
    gotHit = true;
    this->hp--;
    if(this->hp < 0){
        ejectPlayer();
    }

}

void Tank::ejectPlayer(){

}