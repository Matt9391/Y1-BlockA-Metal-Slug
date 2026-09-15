#pragma once

enum ResourceID {
	//dave feeedback to change the null to 0 and set a invalid sprite or smth, 
	// because indexing in -1 is gonna make the game crash
	ID_NULL = -1,
	ID_PLAYER_IDLE_BODY,
	ID_PLAYER_IDLE_LEGS,
	ID_PLAYER_WALK_BODY,
	ID_PLAYER_WALK_LEGS,
	ID_PLAYER_JUMPUP_BODY,
	ID_PLAYER_JUMPUP_LEGS,
	ID_PLAYER_AFTER_RUN_STOP_F, //F stay for full body
	ID_MAP_TILESET,
	ID_COLLISION_TILESET,
	ID_COUNTS
};