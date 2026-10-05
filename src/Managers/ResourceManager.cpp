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
	sprites[ResourceID::ID_PLAYER_PARACHUTE] = new Sprite(new Surface("assets/playerAnimation/parachute.png"), ResourceIDFrames::IDF_PLAYER_PARACHUTE);
	sprites[ResourceID::ID_PLAYER_PARACHUTE_CLOSE] = new Sprite(new Surface("assets/playerAnimation/parachuteClose.png"), ResourceIDFrames::IDF_PLAYER_PARACHUTE_CLOSE);
	sprites[ResourceID::ID_PLAYER_IDLE_BODY] = new Sprite(new Surface("assets/playerAnimation/Pistol/idleBody.png"), ResourceIDFrames::IDF_PLAYER_IDLE_BODY);
	sprites[ResourceID::ID_PLAYER_IDLE_LEGS] = new Sprite(new Surface("assets/playerAnimation/Legs/idleLegs.png"), ResourceIDFrames::IDF_PLAYER_IDLE_LEGS);
	sprites[ResourceID::ID_PLAYER_WALK_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/walkingBody.png"), ResourceIDFrames::IDF_PLAYER_WALK_BODY);
	sprites[ResourceID::ID_PLAYER_WALK_LEGS]= new Sprite(new Surface("assets/playerAnimation/Legs/walkingLegs.png"), ResourceIDFrames::IDF_PLAYER_WALK_LEGS);
	sprites[ResourceID::ID_PLAYER_AFTER_RUN_STOP_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/afterRunStopFullBody.png"), ResourceIDFrames::IDF_PLAYER_AFTER_RUN_STOP_F);
	sprites[ResourceID::ID_PLAYER_JUMPUP_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingBodyUp.png"), ResourceIDFrames::IDF_PLAYER_JUMPUP_BODY);
	sprites[ResourceID::ID_PLAYER_JUMPUP_LEGS]= new Sprite(new Surface("assets/playerAnimation/Legs/jumpingLegsUp.png"), ResourceIDFrames::IDF_PLAYER_JUMPUP_LEGS);
	sprites[ResourceID::ID_PLAYER_CROUCH_IDLE_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/idleBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_CROUCH_IDLE_F);
	sprites[ResourceID::ID_PLAYER_CROUCH_WALKING_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/walkingBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_CROUCH_WALKING_F);
	sprites[ResourceID::ID_PLAYER_FALLING_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/fallingBody.png"), ResourceIDFrames::IDF_PLAYER_FALLING_BODY);
	sprites[ResourceID::ID_PLAYER_FALLING_LEGS]= new Sprite(new Surface("assets/playerAnimation/Legs/fallingLegs.png"), ResourceIDFrames::IDF_PLAYER_FALLING_LEGS);
	sprites[ResourceID::ID_PLAYER_JUMPFORWARD_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/jumpingBodyForward.png"), ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_BODY);
	sprites[ResourceID::ID_PLAYER_JUMPFORWARD_LEGS]= new Sprite(new Surface("assets/playerAnimation/Legs/jumpingLegsForward.png"), ResourceIDFrames::IDF_PLAYER_JUMPFORWARD_LEGS);
	sprites[ResourceID::ID_PLAYER_FALLINGFORWARD_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/fallingBodyForward.png"), ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_BODY);
	sprites[ResourceID::ID_PLAYER_FALLINGFORWARD_LEGS]= new Sprite(new Surface("assets/playerAnimation/Legs/fallingLegsForward.png"), ResourceIDFrames::IDF_PLAYER_FALLINGFORWARD_LEGS);
	sprites[ResourceID::ID_PLAYER_SHOOTING_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/shootingBody.png"), ResourceIDFrames::IDF_PLAYER_SHOOTING_BODY);
	sprites[ResourceID::ID_PLAYER_SHOOTING_UP_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/shootingBodyUp.png"), ResourceIDFrames::IDF_PLAYER_SHOOTING_UP_BODY);
	sprites[ResourceID::ID_PLAYER_SHOOTING_DOWN_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/shootingBodyDown.png"), ResourceIDFrames::IDF_PLAYER_SHOOTING_DOWN_BODY);
	sprites[ResourceID::ID_PLAYER_SHOOTING_CROUCH_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/shootingBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_SHOOTING_CROUCH_F);
	sprites[ResourceID::ID_PLAYER_MELEE_ATTACK_BODY]= new Sprite(new Surface("assets/playerAnimation/Pistol/meleeAttack1Body.png"), ResourceIDFrames::IDF_PLAYER_MELEE_ATTACK_BODY);
	sprites[ResourceID::ID_PLAYER_DIE]= new Sprite(new Surface("assets/playerAnimation/die.png"), ResourceIDFrames::IDF_PLAYER_DIE);
	sprites[ResourceID::ID_PLAYER_DIE_STILL]= new Sprite(new Surface("assets/playerAnimation/dieStill.png"), ResourceIDFrames::IDF_PLAYER_DIE_STILL);
	sprites[ResourceID::ID_PLAYER_REVIVE_F]= new Sprite(new Surface("assets/playerAnimation/Pistol/revive.png"), ResourceIDFrames::IDF_PLAYER_REVIVE_F);
	//* FLAME THROWER
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_IDLE_BODY] = new Sprite(new Surface("assets/playerAnimation/FlameThrower/idleBody.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_IDLE_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_WALK_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/walkingBody.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_WALK_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_AFTER_RUN_STOP_F]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/afterRunStopFullBody.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_AFTER_RUN_STOP_F);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_JUMPUP_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/jumpingBodyUp.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_JUMPUP_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_CROUCH_IDLE_F]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/idleBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_CROUCH_IDLE_F);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_CROUCH_WALKING_F]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/walkingBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_CROUCH_WALKING_F);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_FALLING_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/fallingBody.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_FALLING_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_JUMPFORWARD_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/jumpingBodyForward.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_JUMPFORWARD_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_FALLINGFORWARD_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/fallingBodyForward.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_FALLINGFORWARD_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_SHOOTING_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/shootingBody.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_SHOOTING_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_SHOOTING_UP_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/shootingBodyUp.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_SHOOTING_UP_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_SHOOTING_DOWN_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/shootingBodyDown.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_SHOOTING_DOWN_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_SHOOTING_CROUCH_F]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/shootingBodyCrouch.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_SHOOTING_CROUCH_F);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_MELEE_ATTACK_BODY]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/meleeAttack1Body.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_MELEE_ATTACK_BODY);
	sprites[ResourceID::ID_PLAYER_FLAME_THROWER_REVIVE_F]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/revive.png"), ResourceIDFrames::IDF_PLAYER_FLAME_THROWER_REVIVE_F);


	sprites[ResourceID::ID_REBELSOLDIER_GRANADE]= new Sprite(new Surface("assets/EnemyAnimation/Rebel/grenade.png"), ResourceIDFrames::IDF_REBELSOLDIER_GRANADE);
	sprites[ResourceID::ID_REBELSOLDIER_GRANADE_BOOM]= new Sprite(new Surface("assets/EnemyAnimation/Rebel/grenadeBoom.png"), ResourceIDFrames::IDF_REBELSOLDIER_GRANADE_BOOM);
	sprites[ResourceID::ID_PLAYER_BULLET_PISTOL]= new Sprite(new Surface("assets/playerAnimation/Pistol/bullet.png"), ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL);
	sprites[ResourceID::ID_PLAYER_BULLET_PISTOL_BOOM]= new Sprite(new Surface("assets/playerAnimation/Pistol/bulletBoom.png"), ResourceIDFrames::IDF_PLAYER_BULLET_PISTOL_BOOM);
	sprites[ResourceID::ID_PLAYER_BULLET_FLAME_THROWER]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/bullet.png"), ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER);
	
	sprites[ResourceID::ID_REBELSOLDIER_IDLE] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/idle.png"), ResourceIDFrames::IDF_REBELSOLDIER_IDLE);
	sprites[ResourceID::ID_REBELSOLDIER_WALK] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/walk.png"), ResourceIDFrames::IDF_REBELSOLDIER_WALK);
	sprites[ResourceID::ID_REBELSOLDIER_STOP] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/stop.png"), ResourceIDFrames::IDF_REBELSOLDIER_STOP);
	sprites[ResourceID::ID_REBELSOLDIER_JUMP_UP] =	new Sprite(new Surface("assets/EnemyAnimation/Rebel/jumpup.png"), ResourceIDFrames::IDF_REBELSOLDIER_JUMP_UP);	
	sprites[ResourceID::ID_REBELSOLDIER_JUMP_FORWARD] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/jumpforward.png"), ResourceIDFrames::IDF_REBELSOLDIER_JUMP_FORWARD);
	sprites[ResourceID::ID_REBELSOLDIER_SCARED] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/scared.png"), ResourceIDFrames::IDF_REBELSOLDIER_SCARED);
	sprites[ResourceID::ID_PLAYER_BULLET_FLAME_THROWER_BOOM]= new Sprite(new Surface("assets/playerAnimation/FlameThrower/bulletBoom.png"), ResourceIDFrames::IDF_PLAYER_BULLET_FLAME_THROWER_BOOM);
	sprites[ResourceID::ID_REBELSOLDIER_FALLING] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/falling.png"), ResourceIDFrames::IDF_REBELSOLDIER_FALLING);
	sprites[ResourceID::ID_REBELSOLDIER_COVER] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/cover.png"), ResourceIDFrames::IDF_REBELSOLDIER_COVER);
	sprites[ResourceID::ID_REBELSOLDIER_MELEE_ATTACK] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/meleeAttack.png"), ResourceIDFrames::IDF_REBELSOLDIER_MELEE_ATTACK);
	sprites[ResourceID::ID_REBELSOLDIER_GRANADE_ATTACK] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/granadeAttack.png"), ResourceIDFrames::IDF_REBELSOLDIER_GRANADE_ATTACK);
	sprites[ResourceID::ID_REBELSOLDIER_DEATH] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/death.png"), ResourceIDFrames::IDF_REBELSOLDIER_DEATH);
	sprites[ResourceID::ID_REBELSOLDIER_DEATH_STILL] = new Sprite(new Surface("assets/EnemyAnimation/Rebel/deathStill.png"), ResourceIDFrames::IDF_REBELSOLDIER_DEATH_STILL);
	sprites[ResourceID::ID_POW_IDLE] = new Sprite(new Surface("assets/POWsAnimation/idle.png"), ResourceIDFrames::IDF_POW_IDLE);
	sprites[ResourceID::ID_POW_RELEASING] = new Sprite(new Surface("assets/POWsAnimation/releasing.png"), ResourceIDFrames::IDF_POW_RELEASING);
	sprites[ResourceID::ID_POW_WALK_WAIT] = new Sprite(new Surface("assets/POWsAnimation/walkWait.png"), ResourceIDFrames::IDF_POW_WALK_WAIT);
	sprites[ResourceID::ID_POW_PANTS] = new Sprite(new Surface("assets/POWsAnimation/pants.png"), ResourceIDFrames::IDF_POW_PANTS);
	sprites[ResourceID::ID_POW_BYE] = new Sprite(new Surface("assets/POWsAnimation/bye.png"), ResourceIDFrames::IDF_POW_BYE);
	sprites[ResourceID::ID_POWERUP_CRATE] = new Sprite(new Surface("assets/LootDrops/crate.png"), ResourceIDFrames::IDF_POWERUP_CRATE);
	sprites[ResourceID::ID_POWERUP_FLAME] = new Sprite(new Surface("assets/LootDrops/flame.png"), ResourceIDFrames::IDF_POWERUP_FLAME);
	sprites[ResourceID::ID_POW_RUN_AWAY] = new Sprite(new Surface("assets/POWsAnimation/runAway.png"), ResourceIDFrames::IDF_POW_RUN_AWAY);
	sprites[ResourceID::ID_MAP_TILESET] = new Sprite(new Surface("assets/bg.png"), ResourceIDFrames::IDF_PLAYER_IDLE_LEGS);
	sprites[ResourceID::ID_COLLISION_TILESET] = new Sprite(new Surface("assets/collisionTile.png"), ResourceIDFrames::IDF_COLLISION_TILESET);
	sprites[ResourceID::ID_FONT_ORANGE] = new Sprite(new Surface("assets/fontOrange.png"), ResourceIDFrames::IDF_FONT_ORANGE);
	sprites[ResourceID::ID_FONT_GREY] = new Sprite(new Surface("assets/fontGrey.png"), ResourceIDFrames::IDF_FONT_GREY);
	sprites[ResourceID::ID_FONT_ORANGE_S] = new Sprite(new Surface("assets/fontOrange_9px.png"), ResourceIDFrames::IDF_FONT_ORANGE_S);
	sprites[ResourceID::ID_FONT_GREY_S] = new Sprite(new Surface("assets/fontGrey_9px.png"), ResourceIDFrames::IDF_FONT_GREY_S);
	sprites[ResourceID::ID_FUEL_BAR] = new Sprite(new Surface("assets/fuelBar.png"), ResourceIDFrames::IDF_FUEL_BAR);
	sprites[ResourceID::ID_AMMOS] = new Sprite(new Surface("assets/ammos.png"), ResourceIDFrames::IDF_AMMOS);
	sprites[ResourceID::ID_MENU_BG] = new Sprite(new Surface("assets/menuBg.png"), ResourceIDFrames::IDF_MENU_BG);
	sprites[ResourceID::ID_GAME_OVER_BG] = new Sprite(new Surface("assets/gameOverBg.png"), ResourceIDFrames::IDF_GAME_OVER_BG);

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

const Map& ResourceManager::getMap() const{
	return this->map;
}