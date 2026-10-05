#pragma once

#include <vec2.h>
#include <MapLayer.h>

class Entity;
class Collider;

namespace CollisionManager {

	enum TileType{
		PLATFORM,
		SLOPE_L_TO_R,
		BLOCK,
		SLOPE_R_TO_L,
	};

	bool resolveMapCollision(Entity& e, MapLayer& layer);
		
	bool checkCollision(Collider& a, Collider& b);
	vec2 checkOverlapMapCollision(Collider& collider,const vec2& tilePos,const int& tileSize);
	bool checkMapCollision(Collider& collider, MapLayer& layer, int axis /* 0 = x, 1 = y, -1 = xy*/);
};
