#include "precomp.h"
#include "LootDrop.h"

LootDrop::LootDrop(vec2 pos, EntityType entityType) : 
    Entity(pos, false, entityType)
{

}

void LootDrop::update(float dt) {
    clearSounds();
    getAnimator().playAnimation(dt);
	setColliderSprite();

}