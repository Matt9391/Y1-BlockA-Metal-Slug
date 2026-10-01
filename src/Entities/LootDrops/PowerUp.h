#pragma once
#include <LootDrop.h>

enum PowerUpState{
    PUS_CRATE,
    PUS_REVEALED
};

class PowerUp : public LootDrop {
public:

    PowerUp(vec2 pos, PowerUpState powerUpState);
    ~PowerUp() override;

    void loadGFX() override;

    void applyEffect(Player& pl) override;

private:

};
