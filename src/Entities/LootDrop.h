#pragma once
#include <Entity.h>

class Player;

class LootDrop : public Entity{
public: 
    LootDrop(vec2 pos, EntityType entityType);

	void update(float dt) override;

    virtual void applyEffect(Player& pl) = 0;
};