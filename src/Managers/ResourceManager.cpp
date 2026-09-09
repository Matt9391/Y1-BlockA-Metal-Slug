#include "precomp.h"
#include "ResourceManager.h"
#include <ResourceIDFrames.h>

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
	sprites[ResourceID::ID_PLAYER_IDLE_BODY] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleBody.png"), ResourceIDFrames::IDF_PLAYER_IDLE_BODY);
	sprites[ResourceID::ID_PLAYER_IDLE_LEGS] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleLegs.png"), ResourceIDFrames::IDF_PLAYER_IDLE_LEGS);

	initalized = true;
}

Sprite* ResourceManager::getSprite(ResourceID resourceId) const {
	if (!this->initalized) {
		throw runtime_error("Get sprite before initialized it");
	}
	
	return this->sprites[resourceId];	
}
