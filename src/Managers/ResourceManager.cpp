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
	sprites[ResourceID::ID_PLAYER_AFTER_RUN_STOP_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/afterRunStopFullBody.png"), ResourceIDFrames::IDF_PLAYER_AFTER_RUN_STOP_F);
	sprites[ResourceID::ID_PLAYER_JUMPUP_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingBodyUp.png"), ResourceIDFrames::IDF_PLAYER_JUMPUP_BODY);
	sprites[ResourceID::ID_PLAYER_JUMPUP_LEGS]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingLegsUp.png"), ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS);
	sprites[ResourceID::ID_PLAYER_CROUCH_IDLE_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/idleBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_CROUCH_IDLE_F);
	sprites[ResourceID::ID_PLAYER_CROUCH_WALKING_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/walkingBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_CROUCH_WALKING_F);
	sprites[ResourceID::ID_PLAYER_FALLING_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/fallingBody.png"), ResourceIDFrames::IDF_PLAYER_FALLING_BODY);
	sprites[ResourceID::ID_PLAYER_FALLING_LEGS]= new Sprite(new Surface("assets/playerAnimation/Pistol/fallingLegs.png"), ResourceIDFrames::IDF_PLAYER_FALLING_LEGS);
	sprites[ResourceID::ID_PLAYER_JUMPFORWARD_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingBodyForward.png"), ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_BODY);
	sprites[ResourceID::ID_PLAYER_JUMPFORWARD_LEGS]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingLegsForward.png"), ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_LEGS);
	sprites[ResourceID::ID_PLAYER_FALLINGFORWARD_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/fallingBodyForward.png"), ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_BODY);
	sprites[ResourceID::ID_PLAYER_FALLINGFORWARD_LEGS]= new Sprite(new Surface("assets/playerAnimation/Pistol/fallingLegsForward.png"), ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_LEGS);
	sprites[ResourceID::ID_PLAYER_SHOOTING_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/shootingBody.png"), ResourceIDFrames::IDF_PLAYER_SHOOTING_BODY);
	sprites[ResourceID::ID_PLAYER_SHOOTING_UP_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/shootingBodyUp.png"), ResourceIDFrames::IDF_PLAYER_SHOOTING_UP_BODY);
	sprites[ResourceID::ID_PLAYER_SHOOTING_CROUCH_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/shootingBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_SHOOTING_CROUCH_F);
	sprites[ResourceID::ID_PLAYER_MELEE_ATTACK_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/meleeAttack1Body.png"), ResourceIDFrames::IDF_PLAYER_MELEE_ATTACK_BODY);
	sprites[ResourceID::ID_BULLET_PISTOL]= new Sprite(new Surface("assets/playerAnimation/Pistol/fallingLegs.png"), ResourceIDFrames::IDF_PLAYER_FALLING_LEGS);
	sprites[ResourceID::ID_MAP_TILESET] = new Sprite(new Surface("assets/bg.png"), ResourceIDFrames::IDF_PLAYER_IDLE_LEGS);
	sprites[ResourceID::ID_COLLISION_TILESET] = new Sprite(new Surface("assets/collisionTile.png"), ResourceIDFrames::IDF_COLLISION_TILESET);
	sprites[ResourceID::ID_REBELSOLDIER_IDLE] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/idle.png"), ResourceIDFrames::IDF_REBELSOLDIER_IDLE);
	sprites[ResourceID::ID_REBELSOLDIER_WALK] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/walk.png"), ResourceIDFrames::IDF_REBELSOLDIER_WALK);
	sprites[ResourceID::ID_REBELSOLDIER_STOP] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/stop.png"), ResourceIDFrames::IDF_REBELSOLDIER_STOP);
	sprites[ResourceID::ID_REBELSOLDIER_JUMP_UP] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/jumpup.png"), ResourceIDFrames::IDF_REBELSOLDIER_JUMP_UP);	
	sprites[ResourceID::ID_REBELSOLDIER_JUMP_FORWARD] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/jumpforward.png"), ResourceIDFrames::IDF_REBELSOLDIER_JUMP_FORWARD);
	sprites[ResourceID::ID_REBELSOLDIER_SCARED] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/scared.png"), ResourceIDFrames::IDF_REBELSOLDIER_SCARED);
	sprites[ResourceID::ID_REBELSOLDIER_FALLING] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/falling.png"), ResourceIDFrames::IDF_REBELSOLDIER_FALLING);
	sprites[ResourceID::ID_REBELSOLDIER_COVER] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/cover.png"), ResourceIDFrames::IDF_REBELSOLDIER_COVER);
	sprites[ResourceID::ID_REBELSOLDIER_MELEE_ATTACK] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/meleeAttack.png"), ResourceIDFrames::IDF_REBELSOLDIER_MELEE_ATTACK);
	sprites[ResourceID::ID_REBELSOLDIER_GRANADE_ATTACK] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/granadeAttack.png"), ResourceIDFrames::IDF_REBELSOLDIER_GRANADE_ATTACK);

	initalized = true;
}

Sprite* ResourceManager::getSprite(ResourceID resourceId) const {
	if (!this->initalized) {
		throw runtime_error("Get sprite before initialized it");
	}

	if (resourceId == ResourceID::ID_NULL) {
		return nullptr;
	}
	
	return this->sprites[resourceId];	
}
