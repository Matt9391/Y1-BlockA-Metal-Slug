#pragma once

#include <Entity.h>
#include <InputManager.h>
#include <TankState.h>

class Player;

class Tank : public Entity{
public:
    Tank(vec2 pos, const InputManager& inputManager_);
	~Tank() override;
	void loadGFX() override;

	void update(float dt) override;

    void enterPlayer(Player* player_);

    const TankStates::TankInput getTankInput() const;

    bool hasPlayer() const;

    void takeHit();
private:
    void ejectPlayer();
    
	const InputManager& inputManager; //Const so it can only call const methods
    TankStates::TankState* state;

    Player* player;

    bool gotHit;
    bool dead;
    int hp;
};