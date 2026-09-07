#include "precomp.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager() :
	sprites{},
	initalized(false)
	{}

void ResourceManager::init() {
	sprites[ResourceID::ID_PLAYER_IDLE_BODY] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleBody.png"), 4);
	sprites[ResourceID::ID_PLAYER_IDLE_LEGS] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleLegs.png"), 1);

	initalized = true;
}

Sprite* ResourceManager::getSprite(ResourceID resourceId) const {
	if (!this->initalized) {
		throw new runtime_error("Get sprite before initialized it");
	}
	
	return this->sprites[resourceId];	
}
