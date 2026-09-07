#include "precomp.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager() :
	sprites{},
	initalized(false)
	{}

void ResourceManager::init() {
	sprites[ResourceID::PLAYER_IDLE_BODY] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleBody.png"), 4);

	initalized = true;
}

Sprite* ResourceManager::getSprite(ResourceID resourceId) const {
	if (!this->initalized) {
		throw new runtime_error("Get sprite before initialized it");
	}
	
	return this->sprites[resourceId];
}
