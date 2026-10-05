#pragma once

#include <vec2.h>
#include <MapLayer.h>

class Entity;
struct Collider;

namespace CollisionManager {

	enum TileType{
		PLATFORM,
		SLOPE_L_TO_R,
		BLOCK,
		SLOPE_R_TO_L,
	};

	bool resolveMapCollision(Entity& e, const MapLayer& layer);
		
	bool checkCollision(const Collider& a,const Collider& b);
	vec2 checkOverlapMapCollision(const Collider& collider,const vec2& tilePos,const int& tileSize);
	bool checkMapCollision(const Collider& collider,const MapLayer& layer,const int axis /* 0 = x, 1 = y, -1 = xy*/);
};
