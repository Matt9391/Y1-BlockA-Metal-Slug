#include "precomp.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager() :
	sprites{},
	initalized(false)
	{}

ResourceManager::~ResourceManager() {
	for (int i = 0; i < static_cast<int>(ResourceID::ID_COUNTS); i++) {
		delete sprites[i];
	}
}



void ResourceManager::init() {
	sprites[ResourceID::ID_PLAYER_IDLE_BODY] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleBody.png"), 4);
	sprites[ResourceID::ID_PLAYER_IDLE_LEGS] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleLegs.png"), 1);

	initalized = true;
}

Sprite* ResourceManager::getSprite(ResourceID resourceId) const {
	if (!this->initalized) {
		throw runtime_error("Get sprite before initialized it");
	}
	
	return this->sprites[resourceId];	
}
