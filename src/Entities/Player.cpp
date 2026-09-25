#include "precomp.h"
#include "Player.h"
#include <vec2.h>
#include <iostream>
#include <ResourceManager.h>
#include <PlayerAnimationSet.h>
#include <ResourceIDFrames.h>
#include <RigidBody.h>
#include <InputManager.h>
#include <GunPresets.h>
#include <PlayerState.h>


Player::Player(vec2 pos, InputManager& inputManager) :
	Entity(pos, true),
	inputManager(inputManager),
	state(nullptr),
	gun(this->getPos(), vec2(0, 0), GunPresets::getGun(GunType::PISTOL)), //I need to add gunData templates
	shooting(false),
	hasEnemyInFront(false),
	alive(true),
	enabled(true),
	lives(3),
	score(25001),
	deadTimeElapsed(0.f)
{
	setCollider(vec2(20, 37), vec2(3, 0));
	//setCollider(vec2(20, 7), vec2(3, 30));
	getAnimationSets() = new AnimationSet[PlayerAnimationSet::PAS_COUNTS];
	loadGFX();
	setCurrentASIndex(PlayerAnimationSet::PAS_IDLE);
	state = getPlayerState(static_cast<PlayerAnimationSet>(getCurrentASIndex()));
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

	getRigidBody()->setSpeed(0.1f);
}

Player::~Player() {
	delete[] getAnimationSets();
}

void Player::loadGFX() {
	getAnimationSets()[PlayerAnimationSet::PAS_IDLE] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS,
			ResourceIDFrames::IDF_PLAYER_IDLE_LEGS,
			100,
			vec2(2, 9),
			vec2(-7, 9)),
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_BODY,
			ResourceIDFrames::IDF_PLAYER_IDLE_BODY,
			200,
			vec2(0, 0),
			vec2(-6, 0))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_WALK] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_WALK_LEGS,
			ResourceIDFrames::IDF_PLAYER_WALK_LEGS,
			100,
			vec2(0, 19),
			vec2(-4, 19)),
		AnimationLayer(ResourceID::ID_PLAYER_WALK_BODY,
			ResourceIDFrames::IDF_PLAYER_WALK_BODY,
			90,
			vec2(2, -2),
			vec2(-7, -2))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_AFTER_RUN_STOP] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_AFTER_RUN_STOP_F,
			ResourceIDFrames::IDF_PLAYER_AFTER_RUN_STOP_F,
			150,
			vec2(3, 1),
			vec2(-8, 1))
	);

	
	getAnimationSets()[PlayerAnimationSet::PAS_CROUCH_IDLE] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_CROUCH_IDLE_F,
			ResourceIDFrames::IDF_PLAYER_CROUCH_IDLE_F,
			150,
			vec2(3, 14),
			vec2(-5, 14))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_CROUCH_WALKING] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_CROUCH_WALKING_F,
			ResourceIDFrames::IDF_PLAYER_CROUCH_WALKING_F,
			150,
			vec2(3, 14),
			vec2(-5, 14))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_JUMP_UP] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS,
			80,
			vec2(7, 20),
			vec2(0, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_BODY,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_BODY,
			80,
			vec2(0, -3),
			vec2(-2, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_FALLING] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_FALLING_LEGS,
			ResourceIDFrames::IDF_PLAYER_FALLING_LEGS,
			100,
			vec2(7, 20),
			vec2(0, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_FALLING_BODY,
			ResourceIDFrames::IDF_PLAYER_FALLING_BODY,
			100,
			vec2(0, -3),
			vec2(-2, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_JUMP_FORWARD] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPFORWARD_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_LEGS,
			100,
			vec2(0, 18),
			vec2(-4, 18)),
		AnimationLayer(ResourceID::ID_PLAYER_JUMPFORWARD_BODY,
			ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_BODY,
			100,
			vec2(0, -3),
			vec2(-4, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_FALLING_FORWARD] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_FALLINGFORWARD_LEGS,
			ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_LEGS,
			100,
			vec2(5, 18),
			vec2(-5, 18)),
		AnimationLayer(ResourceID::ID_PLAYER_FALLINGFORWARD_BODY,
			ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_BODY,
			100,
			vec2(-2, -3),
			vec2(-4, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_IDLE] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS,
			ResourceIDFrames::IDF_PLAYER_IDLE_LEGS,
			100,
			vec2(2, 9),
			vec2(-7, 9)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_BODY,
			80,
			vec2(-1, -2),
			vec2(-23, 0))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_WALK] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_WALK_LEGS,
			ResourceIDFrames::IDF_PLAYER_WALK_LEGS,
			100,
			vec2(0, 19),
			vec2(-4, 19)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_BODY,
			80,
			vec2(0, -4),
			vec2(-24, -4))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_IDLE_UP] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS,
			ResourceIDFrames::IDF_PLAYER_IDLE_LEGS,
			100,
			vec2(2, 9),
			vec2(-6, 9)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_UP_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_UP_BODY,
			80,
			vec2(0, -42),
			vec2(-4, -42))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_WALK_UP] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_WALK_LEGS,
			ResourceIDFrames::IDF_PLAYER_WALK_LEGS,
			100,
			vec2(0, 19),
			vec2(-5, 19)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_UP_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_UP_BODY,
			80,
			vec2(0, -42),
			vec2(-3, -42))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_CROUCH] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_CROUCH_F,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_CROUCH_F,
			80,
			vec2(3, 8),
			vec2(-22, 8))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_JUMP_UP] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS,
			80,
			vec2(6, 20),
			vec2(0, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_BODY,
			80,
			vec2(0, -3),
			vec2(-25, -3))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_UP_JUMP_UP] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS,
			80,
			vec2(6, 20),
			vec2(0, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_UP_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_UP_BODY,
			80,
			vec2(0, -42),
			vec2(-4, -42))
	);
	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_JUMP_FORWARD] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPFORWARD_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_LEGS,
			100,
			vec2(0, 18),
			vec2(-4, 18)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_BODY,
			80,
			vec2(-1, -2),
			vec2(-23, 0))
	);
	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_JUMP_DOWN] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS,
			80,
			vec2(6, 20),
			vec2(0, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_DOWN_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_DOWN_BODY,
			80,
			vec2(4, 3),
			vec2(-2, 3))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_MELEE_ATTACK_IDLE] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS,
			ResourceIDFrames::IDF_PLAYER_IDLE_LEGS,
			100,
			vec2(2, 9),
			vec2(-7, 9)),
		AnimationLayer(ResourceID::ID_PLAYER_MELEE_ATTACK_BODY,
			ResourceIDFrames::IDF_PLAYER_MELEE_ATTACK_BODY,
			80,
			vec2(-7, -15),
			vec2(-10, -15))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_MELEE_ATTACK_WALK] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_WALK_LEGS,
			ResourceIDFrames::IDF_PLAYER_WALK_LEGS,
			100,
			vec2(0, 19),
			vec2(-4, 19)),
		AnimationLayer(ResourceID::ID_PLAYER_MELEE_ATTACK_BODY,
			ResourceIDFrames::IDF_PLAYER_MELEE_ATTACK_BODY,
			80,
			vec2(-7, -15),
			vec2(-10, -15))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_DIE] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_DIE,
			ResourceIDFrames::IDF_PLAYER_DIE,
			80,
			vec2(-7, 0),
			vec2(-10,0))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_DIE_STILL] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_DIE_STILL,
			ResourceIDFrames::IDF_PLAYER_DIE_STILL,
			80,
			vec2(-7, 0),
			vec2(-10, 0))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_REVIVE] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_REVIVE_F,
			ResourceIDFrames::IDF_PLAYER_REVIVE_F,
			100,
			vec2(0, -205),
			vec2(-10, -205))
	);



	//setCurrentASIndex(PlayerAnimationSet::PAS_SHOOTING_IDLE);
	//getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], true);
	//getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], false);
}

Gun& Player::getGun() {
	return gun;
}

int Player::getGunBullets() {
	return gun.getBulletsCount();
}


void Player::setEnemyInFront(bool enemyInFront) {
	this->hasEnemyInFront = enemyInFront;
}

bool Player::getEnemyInFront() const {
	return this->hasEnemyInFront;
}

int Player::getLives() const {
	return this->lives;
}

int Player::getScore() const {
	return this->score;
}

void Player::takeHit() {
	this->lives--;
	setLifeState(false);
	if (lives == -1) {
		
	}
}

void Player::setLifeState(bool state) {
	alive = state;
	enabled = state;
}

void Player::revive() {
	setLifeState(true);
	deadTimeElapsed = 0.f;
}


void Player::update(float dt) {
	if (!alive) deadTimeElapsed += dt;

	getAnimator().playAnimation(dt);

	//dt = fminf(dt, 0.05f);

	PlayerInput pInput = getPlayerInput();

	//std::cout << pInput.inputDown << "and state: " << getDir().y << std::endl;


	handleMovement(dt, pInput);
	PlayerAnimationSet nextState = state->handleInput(pInput, static_cast<PlayerAnimationSet>(getCurrentASIndex()));
	//std::cout << nextState << std::endl;
	if (nextState == PlayerAnimationSet::PAS_REVIVE) {
		if (deadTimeElapsed > DEADTIMER) {
			setCurrentASIndex(nextState);
			state = getPlayerState(static_cast<PlayerAnimationSet>(getCurrentASIndex()));
			revive();
		}
	}
	else {
		setCurrentASIndex(nextState);
		state = getPlayerState(static_cast<PlayerAnimationSet>(getCurrentASIndex()));
	}

	//handleAnimationSet(isMoving, isJumping, isGrounded);

	if (pInput.isShooting) {
		if (!pInput.enemyInFront) {
			gun.shoot();
			setShooting(true);
		}
	}
	else {
		setShooting(false);
	}

	//set gun shooting direction
	{
		int x = 1;
		int y = 0;
		
	
		
		{


			if (getLastDir().x < 0) {
				x = -1;
			}

			if (pInput.inputUp) {
				if (!gun.getCanShootDiagonally()) {
					x = 0;
				}

				y = -1;
			}

			if (!pInput.isGrounded) {
				if (pInput.inputDown) {
					y = 1;
					x = 0;
				}
			}
		}
		if (gun.getCanShootDiagonally()) {

			if (pInput.inputLeft && pInput.inputUp) {
				x = -1;
				y = -1;
			}
			else if (pInput.inputRight && pInput.inputUp) {
				x = 1;
				y = -1;
			}
			else if (pInput.inputUp) {
				x = 0;
				y = -1;
			}
		}

		gun.setShootDir(vec2(x,y));
	}

	const bool flip = getLastDir().x < 0;
	const bool reset = pInput.isShooting;
	//setColliderOffset(flip ? vec2(-15, 0) : vec2(3, 0));
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], flip, reset);

	gun.update(dt);
}

PlayerInput Player::getPlayerInput() {
	const bool inputRight = inputManager.isKeyPressed('D');
	const bool inputLeft = inputManager.isKeyPressed('A');
	const bool inputUp = inputManager.isKeyPressed('W');
	const bool inputDown = inputManager.isKeyPressed('S');
	const bool isMoving = inputRight || inputLeft;
	const bool isCrouching = inputDown;
	const bool isJumping = inputManager.isKeyJustPressed(' ');
	const bool isGrounded = getRigidBody()->isGrounded();
	const bool isShooting = inputManager.isKeyJustPressed('F');
	const bool enemyInFront = getEnemyInFront();
	const bool dead = !alive;
	const bool lost = lives < 0;



	//printf("PlayerInput { right=%d, left=%d, moving=%d, jumping=%d, grounded=%d, crouching=%d, shooting=%d, animEnd=%d, dirY=%d }\n", inputRight, inputLeft, isMoving, isJumping, isGrounded, false, isShooting, getAnimator().isAnimationEnded(), getDir().y);

	//struct PlayerInput
	//{
	//	bool inputRight;
	//	bool inputLeft;
	//	bool isMoving;
	//	bool isJumping;
	//	bool isGrounded;
	//	bool isCrouching;
	//	bool isShooting;
	//	bool onAnimationEnd;
	//	int  dirY; // -1 = aiming up, 0 = neutral, 1 = aiming down
	//};

	const PlayerInput playerInput = {
		inputRight,
		inputLeft,
		inputUp,
		inputDown,
		isMoving,
		isJumping,
		isGrounded,
		isCrouching,
		isShooting,
		enemyInFront,
		getAnimator().isAnimationEnded(),
		dead,
		lost
	};

	return playerInput;
}

void Player::handleMovement(float dt, const PlayerInput& pInput) {

	RigidBody* rb = getRigidBody();

	if (getDir().x != 0)
		setLastDir(getDir());
	setDir(vec2(0, 0));

	//Movement
	if (pInput.inputRight) {
		setDir(vec2(1, 0));
	}
	else if (pInput.inputLeft) {
		setDir(vec2(-1, 0));
	}else if (pInput.inputDown) {
		setDir(vec2(getDir().x, 1));
	}
	else if (pInput.inputUp) {
		setDir(vec2(getDir().x, -1));
	}

	if (pInput.inputDown && getCurrentASIndex() == PAS_SHOOTING_CROUCH) {
		setDir(vec2(0.f, 1.f));
	}


	rb->setVelocityX(rb->getSpeed() * getDir().x);

	if (!pInput.isGrounded) {
		rb->addVelocity(vec2(0, rb->getGravity() * dt));
	}
	else {
		rb->setVelocityY(0);
		if (enabled && pInput.isJumping) {
			rb->addVelocity(vec2(0, -0.37f));
			setGrounded(false);
		}
	}

	if (!enabled) {
		rb->setVelocityX(0);
		setDir(vec2(0, 0));
	}

	this->addToPos(rb->getVelocity() * dt);

}
void Player::handleAnimationSet(bool isMoving, bool isJumping, bool isGrounded) {

	//Animations
	if (isMoving) {
		if (isGrounded) {

			if (isJumping) {
				setCurrentASIndex(PlayerAnimationSet::PAS_JUMP_UP);
			}
			else {
				setCurrentASIndex(PlayerAnimationSet::PAS_WALK);
			}

		}
	}
	else if (isGrounded && isJumping) {
		setCurrentASIndex(PlayerAnimationSet::PAS_JUMP_UP);
	}
	else if (isGrounded && getCurrentASIndex() == PlayerAnimationSet::PAS_WALK) {
		setCurrentASIndex(PlayerAnimationSet::PAS_AFTER_RUN_STOP);
	}
	else if (isGrounded && getCurrentASIndex() == PlayerAnimationSet::PAS_AFTER_RUN_STOP && getAnimator().isAnimationEnded()) {
		setCurrentASIndex(PlayerAnimationSet::PAS_IDLE);
	}
	else if (isGrounded && getCurrentASIndex() == PlayerAnimationSet::PAS_FALLING) {
		setCurrentASIndex(PlayerAnimationSet::PAS_IDLE);
	}
	else if (getCurrentASIndex() == PlayerAnimationSet::PAS_JUMP_UP && getAnimator().isAnimationEnded()) {
		setCurrentASIndex(PlayerAnimationSet::PAS_FALLING);
	}
}

void Player::setShooting(bool shooting) {
	this->shooting = shooting;
}

bool Player::isShooting() const{
	return this->shooting;
}