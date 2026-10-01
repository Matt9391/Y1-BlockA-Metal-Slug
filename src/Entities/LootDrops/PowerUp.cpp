#include "precomp.h"
#include "PowerUp.h"
#include <ResourceIDFrames.h>

PowerUp::PowerUp(vec2 pos, PowerUpState PowerUpState) :
    LootDrop(pos)
    {
        
        setCollider(vec2(32,32), vec2(0,0));
        getAnimationSets() = new AnimationSet[2];
        loadGFX();
        setCurrentASIndex(PowerUpState);
        getAnimator().setAnimation(&getAnimationSets()[getCurrentASIndex()]);

    }
PowerUp::~PowerUp(){
    delete[] getAnimationSets();
}


void PowerUp::loadGFX() {
    getAnimationSets()[PowerUpState::PUS_CRATE] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_POWERUP_CRATE,
            ResourceIDFrames::IDF_POWERUP_CRATE,
            100,
            vec2(0,0),
            vec2(0,0)
        ));
    getAnimationSets()[PowerUpState::PUS_REVEALED] = AnimationSet(
        1,
        AnimationLayer(
            ResourceID::ID_POWERUP_FLAME,
            ResourceIDFrames::IDF_POWERUP_FLAME,
            100,
            vec2(0,0),
            vec2(0,0)
        ));
}


void PowerUp::applyEffect(Player& pl){

}