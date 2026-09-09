#pragma once

enum ResourceIDFrames {
	// This enum just exist because we cant fuck use the hash maps. so yeah, you take it
	// keep track of the frames of the sprite
	IDF_NULL = -1,
	IDF_PLAYER_IDLE_BODY = 4,
	IDF_PLAYER_IDLE_LEGS = 1,
	IDF_MAP_TILESET = 1,
	IDF_COLLISION_TILESET = 1
};