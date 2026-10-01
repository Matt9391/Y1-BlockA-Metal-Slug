#include "precomp.h"
#include "LootDrop.h"

LootDrop::LootDrop(vec2 pos) : 
    Entity(pos, false, ET_LOOTDROP)
{

}

void LootDrop::update(float dt) {
    getAnimator().playAnimation(dt);
}