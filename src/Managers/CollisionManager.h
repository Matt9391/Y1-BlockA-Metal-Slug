#pragma once

#include <vec2.h>
#include <MapLayer.h>

class Entity;
class Collider;

namespace CollisionManager {

	bool resolveMapCollision(Entity& e, MapLayer& layer);
		
	bool checkCollision(Collider& a, Collider& b);
	bool checkMapCollision(Collider& collider, MapLayer& layer, int axe /* 0 = x, 1 = y, -1 = xy*/);
};
