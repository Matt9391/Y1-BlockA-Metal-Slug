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

	void init(vec2 pos_);
	void loadGFX() override;

	void update(float dt) override;

	bool isShooting() const;

	Gun& getGun();
	int getGunBullets() const;
	void setGunData(GunData newData);

	void setEntityInFront(bool enemyInFront);
	
	int getLives() const;
	int getScore() const;

	void takeHit();

	void revive();
	void fullRevive();

	bool getEnabled() const;

	void addPowSaved();
	int getPowSaved() const;
private:
	bool getEnemyInFront() const;
	void setShooting(bool shooting_);
	const PlayerInput getPlayerInput() const;
	void handleMovement(float dt, const PlayerInput& pInput);

	void setLifeState(bool state_);

	const InputManager& inputManager; //Const so it can only call const methods
	Gun gun;
	PlayerState* state;

	bool shooting;
	bool hasEntityInFront;
	bool alive;
	bool enabled;

	int lives;
	int score;

	float deadTimeElapsed;
	static const int DEADTIMER = 2500;

	bool canRevive;
	float gravityMultiplier;

	int powSaved;
};

