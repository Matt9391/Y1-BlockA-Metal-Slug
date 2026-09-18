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
	gun(this->getPos(), vec2(0, 0), GunPresets::getGun(GunType::PISTOL)) //I need to add gunData templates
{
	setCollider(vec2(20, 37), vec2(3, 0));
	//setCollider(vec2(20, 7), vec2(3, 30));
	getAnimationSets() = new AnimationSet[PlayerAnimationSet::PAS_COUNTS];
	loadGFX();
	setCurrentASIndex(PlayerAnimationSet::PAS_IDLE);
	state = getPlayerState(static_cast<PlayerAnimationSet>(getCurrentASIndex()));
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);
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
			vec2(-23, 9)),
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_BODY,
			ResourceIDFrames::IDF_PLAYER_IDLE_BODY,
			200,
			vec2(0, 0),
			vec2(-22, 0))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_WALK] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_WALK_LEGS,
			ResourceIDFrames::IDF_PLAYER_WALK_LEGS,
			100,
			vec2(0, 19),
			vec2(-22, 19)),
		AnimationLayer(ResourceID::ID_PLAYER_WALK_BODY,
			ResourceIDFrames::IDF_PLAYER_WALK_BODY,
			90,
			vec2(2, -2),
			vec2(-25, -2))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_AFTER_RUN_STOP] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_AFTER_RUN_STOP_F,
			ResourceIDFrames::IDF_PLAYER_AFTER_RUN_STOP_F,
			150,
			vec2(3, 1),
			vec2(-25, 1))
	);

	
	getAnimationSets()[PlayerAnimationSet::PAS_CROUCH_IDLE] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_CROUCH_IDLE_F,
			ResourceIDFrames::IDF_PLAYER_CROUCH_IDLE_F,
			150,
			vec2(3, 14),
			vec2(-25, 14))
	);
	
	getAnimationSets()[PlayerAnimationSet::PAS_CROUCH_WALKING] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_CROUCH_WALKING_F,
			ResourceIDFrames::IDF_PLAYER_CROUCH_WALKING_F,
			150,
			vec2(3, 14),
			vec2(-25, 14))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_AFTER_RUN_STOP] = AnimationSet(
		1,
		AnimationLayer(ResourceID::ID_PLAYER_AFTER_RUN_STOP_F,
			ResourceIDFrames::IDF_PLAYER_AFTER_RUN_STOP_F,
			150,
			vec2(3, 1),
			vec2(-25, 1))
	);
	getAnimationSets()[PlayerAnimationSet::PAS_JUMP_UP] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS,
			80,
			vec2(7, 20),
			vec2(-23, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_JUMPUP_BODY,
			ResourceIDFrames::IDF_PLAYER_JUMPUP_BODY,
			80,
			vec2(0, -3),
			vec2(-25, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_FALLING] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_FALLING_LEGS,
			ResourceIDFrames::IDF_PLAYER_FALLING_LEGS,
			100,
			vec2(7, 20),
			vec2(-23, 20)),
		AnimationLayer(ResourceID::ID_PLAYER_FALLING_BODY,
			ResourceIDFrames::IDF_PLAYER_FALLING_BODY,
			100,
			vec2(0, -3),
			vec2(-25, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_JUMP_FORWARD] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_JUMPFORWARD_LEGS,
			ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_LEGS,
			100,
			vec2(0, 18),
			vec2(-25, 18)),
		AnimationLayer(ResourceID::ID_PLAYER_JUMPFORWARD_BODY,
			ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_BODY,
			100,
			vec2(0, -3),
			vec2(-25, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_FALLING_FORWARD] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_FALLINGFORWARD_LEGS,
			ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_LEGS,
			100,
			vec2(5, 18),
			vec2(-26, 18)),
		AnimationLayer(ResourceID::ID_PLAYER_FALLINGFORWARD_BODY,
			ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_BODY,
			100,
			vec2(-2, -3),
			vec2(-25, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_FALLING_FORWARD] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_FALLINGFORWARD_LEGS,
			ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_LEGS,
			100,
			vec2(5, 18),
			vec2(-26, 18)),
		AnimationLayer(ResourceID::ID_PLAYER_FALLINGFORWARD_BODY,
			ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_BODY,
			100,
			vec2(-2, -3),
			vec2(-25, -3))
	);

	getAnimationSets()[PlayerAnimationSet::PAS_SHOOTING_IDLE] = AnimationSet(
		2,
		AnimationLayer(ResourceID::ID_PLAYER_IDLE_LEGS,
			ResourceIDFrames::IDF_PLAYER_IDLE_LEGS,
			100,
			vec2(2, 9),
			vec2(-23, 9)),
		AnimationLayer(ResourceID::ID_PLAYER_SHOOTING_BODY,
			ResourceIDFrames::IDF_PLAYER_SHOOTING_BODY,
			80,
			vec2(-1, -2),
			vec2(-42, 0))
	);



	setCurrentASIndex(PlayerAnimationSet::PAS_SHOOTING_IDLE);
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], true);
	//getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], false);
}

Gun& Player::getGun() {
	return gun;
}

int Player::getGunBullets() {
	return gun.getBulletsCount();
}

void Player::update(float dt) {
	getAnimator().playAnimation(dt);

	//dt = fminf(dt, 0.05f);

	PlayerInput pInput = getPlayerInput();

	//std::cout << pInput.inputDown << "and state: " << getDir().y << std::endl;


	handleMovement(dt, pInput.inputDown, pInput.inputRight, pInput.inputLeft, pInput.isJumping, pInput.isGrounded);
	PlayerAnimationSet nextState = state->handleInput(pInput, static_cast<PlayerAnimationSet>(getCurrentASIndex()));
	//std::cout << nextState << std::endl;
	state = getPlayerState(static_cast<PlayerAnimationSet>(getCurrentASIndex()));
	setCurrentASIndex(nextState);

	//handleAnimationSet(isMoving, isJumping, isGrounded);

	if (pInput.isShooting) {
		gun.shoot();
	}

	const bool flip = getDir().x == 0 ? getLastDir().x < 0 : getDir().x < 0;
	setColliderOffset(flip ? vec2(-15, 0) : vec2(3, 0));
	getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()], flip);

	gun.update(dt);
}

PlayerInput Player::getPlayerInput() {
	const bool inputRight = inputManager.isKeyPressed('D');
	const bool inputLeft = inputManager.isKeyPressed('A');
	const bool inputDown = inputManager.isKeyPressed('S');
	const bool isMoving = inputRight || inputLeft;
	const bool isCrouching = inputDown;
	const bool isJumping = inputManager.isKeyJustPressed(' ');
	const bool isGrounded = getRigidBody()->isGrounded();
	const bool isShooting = inputManager.isKeyJustPressed('F');


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
		inputDown,
		inputRight,
		inputLeft,
		isMoving,
		isJumping,
		isGrounded,
		isCrouching,
		isShooting,
		getAnimator().isAnimationEnded(),
		getDir().y
	};

	return playerInput;
}

void Player::handleMovement(float dt,bool inputDown, bool inputRight, bool inputLeft, bool isJumping, bool isGrounded) {
	if (getDir() != 0)
		setLastDir(getDir());
	setDir(vec2(0, inputDown ? 1 : 0));

	//Movement
	if (inputRight) {
		setDir(vec2(1, 0));
	}
	else if (inputLeft) {
		setDir(vec2(-1, 0));
	}


	//if(isMoving){
	//}
	getRigidBody()->setVelocityX(0.1f * getDir().x);

	if (!isGrounded) {
		getRigidBody()->addVelocity(vec2(0, 0.001f * dt));
	}
	else {
		getRigidBody()->setVelocityY(0);
		if (isJumping) {
			getRigidBody()->addVelocity(vec2(0, -0.37f));
			setGrounded(false);
		}
	}


	this->addToPos(getRigidBody()->getVelocity() * dt);

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

