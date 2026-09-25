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

	bool isShooting() const;

	Gun& getGun();
	int getGunBullets();

	void setEnemyInFront(bool enemyInFront);
	
	int getLives() const;
	int getScore() const;

	void takeHit();

	void revive();
private:
	bool getEnemyInFront() const;
	void setShooting(bool shooting);
	PlayerInput getPlayerInput();
	void handleMovement(float dt, const PlayerInput& pInput);
	void handleAnimationSet(bool isMoving, bool isJumping, bool isGrounded);

	void setLifeState(bool state);

	const InputManager& inputManager; //Const so it can only call const methods
	Gun gun;
	PlayerState* state;

	bool shooting;
	bool hasEnemyInFront;
	bool alive;
	bool enabled;

	int lives;
	int score;

	float deadTimeElapsed;
	static const int DEADTIMER = 2500;
};

