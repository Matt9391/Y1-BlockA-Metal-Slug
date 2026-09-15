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
	sprites[ResourceID::ID_PLAYER_WALK_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/walkingBody.png"), ResourceIDFrames::IDF_PLAYER_WALK_BODY);
	sprites[ResourceID::ID_PLAYER_WALK_LEGS]= new Sprite(new Surface("assets/playerAnimation/Pistol/walkingLegs.png"), ResourceIDFrames::IDF_PLAYER_WALK_LEGS);
	sprites[ResourceID::ID_PLAYER_JUMPUP_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingBodyUp.png"), ResourceIDFrames::IDF_PLAYER_JUMPUP_BODY);
	sprites[ResourceID::ID_PLAYER_JUMPUP_LEGS]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingLegsUp.png"), ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS);
	sprites[ResourceID::ID_PLAYER_AFTER_RUN_STOP_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/afterRunStopFullBody.png"), ResourceIDFrames::IDF_PLAYER_AFTER_RUN_STOP_F);
	sprites[ResourceID::ID_MAP_TILESET] = new Sprite(new Surface("assets/bg.png"), ResourceIDFrames::IDF_PLAYER_IDLE_LEGS);
	sprites[ResourceID::ID_COLLISION_TILESET] = new Sprite(new Surface("assets/collisionTile.png"), ResourceIDFrames::IDF_COLLISION_TILESET);
	
	initalized = true;
}

Sprite* ResourceManager::getSprite(ResourceID resourceId) const {
	if (!this->initalized) {
		throw runtime_error("Get sprite before initialized it");
	}
	
	return this->sprites[resourceId];	
}
