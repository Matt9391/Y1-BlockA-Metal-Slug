#pragma once
#include <Entity.h>
#include <AnimationSet.h>
#include <InputManager.h>
#include <Gun.h>

class Tmpl8::Sprite;
class ResourceManager;
class PlayerState;
struct PlayerInput;

class Player : public Entity
{
public:
	Player(vec2 pos, InputManager& inputManager);
	~Player() override;

	void loadGFX() override;

	void update(float dt) override;

	Gun& getGun();
	int getGunBullets();

private:
	PlayerInput getPlayerInput();
	void handleMovement(float dt, bool inputDown, bool inputRight, bool inputLeft, bool isJumping, bool isGrounded);
	void handleAnimationSet(bool isMoving, bool isJumping, bool isGrounded);
	const InputManager& inputManager; //Const so it can only call const methods
	Gun gun;
	PlayerState* state;
};

