#include "precomp.h"
#include "CollisionManager.h"
#include <iostream>


namespace CollisionManager {

	vec2 resolveMapCollision(Entity& e, MapLayer& layer) {
			Collider& collider = e.getCollider();
			vec2 startPos = vec2(static_cast<int>(e.getPos().x / layer.tileSize),
								 static_cast<int>(e.getPos().y / layer.tileSize));
			//vec2 endPosition = ; //bottom right
			vec2 endPos = vec2(static_cast<int>((e.getPos().x + e.getCollider().size.x) / layer.tileSize),
							   static_cast<int>((e.getPos().y + e.getCollider().size.y) / layer.tileSize)); //bottom right
			//std::cout << "startX: " << startPos.x << "endX: " << endPos.x << std::endl;
			//std::cout << "startY: " << startPos.y << "endY: " << endPos.y << std::endl;

			for (int i = startPos.y; i <= endPos.y; i++) {
				for (int j = startPos.x; j <= endPos.x; j++) {
					int tileId = layer.data[i * static_cast<int>(layer.tiles.x) + j];
					if (tileId == 0) continue;

					int tileX = j * layer.tileSize;
					int tileY = i * layer.tileSize;

					float leftTile = tileX;
					float rightTile = tileX + layer.tileSize;
					float topTile = tileY;
					float bottomTile = tileY + layer.tileSize;

					float overlapX = fminf(rightTile, collider.pos.x + collider.size.x) - fmaxf(leftTile, collider.pos.x);
					float overlapY = fminf(bottomTile, collider.pos.y + collider.size.y) - fmaxf(topTile, collider.pos.y);


					vec2 eCenter = vec2(collider.pos.x + collider.size.x / 2, collider.pos.y + collider.size.y / 2);
					vec2 tCenter = vec2(tileX + layer.tileSize / 2, tileY + layer.tileSize / 2); //tile Center

					vec2 dir = vec2(eCenter.x < tCenter.x ? -1 : 1, eCenter.y < tCenter.y ? -1 : 1);

					if (overlapX > 0 && overlapY > 0) {
						if (overlapX < overlapY) {
							e.addToPos(vec2(overlapX * dir.x, 0));
						}
						else {
							e.addToPos(vec2(0, overlapY * dir.y));
						}
						e.setGrounded(true);
					}

				
					//if (overlapX > 0) 
					//if (overlapY > 0) e.addToPos(vec2(0,-overlapY));
				}
			}
			
			
			return { 0,0 };
	}
} 