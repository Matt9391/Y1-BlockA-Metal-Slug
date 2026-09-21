#include "precomp.h"
#include "CollisionManager.h"
#include <iostream>
#include <Entity.h>
#include <Collider.h>
#include <myMath.h>


namespace CollisionManager {

	//bool resolveMapCollision(Entity& e, MapLayer& layer) {
	//		Collider& collider = e.getCollider();
	//		vec2 startPos = vec2(static_cast<int>(e.getPos().x / layer.tileSize),
	//							 static_cast<int>(e.getPos().y / layer.tileSize));
	//		//vec2 endPosition = ; //bottom right
	//		vec2 endPos = vec2(static_cast<int>((e.getPos().x + e.getCollider().size.x) / layer.tileSize),
	//						   static_cast<int>((e.getPos().y + e.getCollider().size.y) / layer.tileSize)); //bottom right
	//		//std::cout << "startX: " << startPos.x << "endX: " << endPos.x << std::endl;
	//		//std::cout << "startY: " << startPos.y << "endY: " << endPos.y << std::endl;

	//		bool grounded = false;

	//		for (int i = startPos.y; i <= endPos.y; i++) {
	//			for (int j = startPos.x; j <= endPos.x; j++) {
	//				int tileId = layer.data[i * static_cast<int>(layer.tiles.x) + j] - layer.firstgid;
	//				if (tileId == -layer.firstgid) continue;

	//				switch (tileId)
	//				{
	//					case 1:
	//						break;
	//					case 0:
	//					case 2:
	//					{
	//						int tileX = j * layer.tileSize;
	//						int tileY = i * layer.tileSize;
	//						
	//						
	//						if (tileId == 0) {
	//							//if (collider.pos.y + collider.size.y > tileY + layer.tileSize * 0.05f) break;
	//							if (e.getVelocity().y <= 0) break;
	//						}


	//						float leftTile = tileX;
	//						float rightTile = tileX + layer.tileSize;
	//						float topTile = tileY;
	//						float bottomTile = tileY + layer.tileSize;

	//						float overlapX = fminf(rightTile, collider.pos.x + collider.size.x) - fmaxf(leftTile, collider.pos.x);
	//						float overlapY = fminf(bottomTile, collider.pos.y + collider.size.y) - fmaxf(topTile, collider.pos.y);

	//						vec2 eCenter = vec2(collider.pos.x  + collider.size.x / 2, collider.pos.y + collider.size.y / 2);
	//						vec2 tCenter = vec2(tileX + layer.tileSize / 2, tileY + layer.tileSize / 2); //tile Center


	//						vec2 dir = vec2(eCenter.x < tCenter.x ? -1 : 1, eCenter.y < tCenter.y ? -1 : 1);

	//						if (overlapX > -0.01f && overlapY > -0.01f) {
	//							if (overlapX < overlapY) {
	//								e.addToPos(vec2(overlapX * dir.x, 0));
	//							}
	//							else {
	//								e.addToPos(vec2(0, overlapY * dir.y));
	//								grounded = true;
	//							}
	//						}
	//					}
	//						break;
	//					default:
	//						break;
	//				}
	//				
	//			}
	//		}
	//		
	//		e.setGrounded(grounded);

	//		return true;
	//}

	bool resolveMapCollision(Entity& e, MapLayer& layer) {
			Collider& collider = e.getCollider();
			vec2 startPos = vec2(static_cast<int>((e.getPos().x + collider.offset.x) / layer.tileSize),
								 static_cast<int>((e.getPos().y + collider.offset.y) / layer.tileSize));
			//vec2 endPosition = ; //bottom right
			vec2 endPos = vec2(static_cast<int>((e.getPos().x + collider.offset.x + e.getCollider().size.x) / layer.tileSize),
							   static_cast<int>((e.getPos().y + collider.offset.y + e.getCollider().size.y) / layer.tileSize)); //bottom right
			//std::cout << "startX: " << startPos.x << "endX: " << endPos.x << std::endl;
			//std::cout << "startY: " << startPos.y << "endY: " << endPos.y << std::endl;

			bool grounded = false;
			bool collided = false;

			for (int i = startPos.y; i <= endPos.y; i++) {
				if (i < 0 || i >= layer.tiles.y)
					continue;
				for (int j = startPos.x; j <= endPos.x; j++) {
					if (j < 0 || j >= layer.tiles.x)
						continue;

					const vec2 colliderPos = (collider.pos + collider.offset); //recompile it everytime because it changes but since its not a reference it need to be recompiled
					//std::cout << i * static_cast<int>(layer.tiles.x) + j << std::endl;
					int tileId = layer.data[i * static_cast<int>(layer.tiles.x) + j] - layer.firstgid;
					if (tileId == -layer.firstgid) continue;

					switch (tileId)
					{
						case 1:
						case 3:
						{
							int tileX = j * layer.tileSize;
							int tileY = i * layer.tileSize;

							float leftTile = tileX;
							float rightTile = tileX + layer.tileSize;
							float topTile = tileY;
							float bottomTile = tileY + layer.tileSize;

							float overlapX = fminf(rightTile, colliderPos.x + collider.size.x) - fmaxf(leftTile, colliderPos.x);
							float overlapY = fminf(bottomTile, colliderPos.y + collider.size.y) - fmaxf(topTile, colliderPos.y);

							if (overlapX > -0.01f && overlapY > -0.01f) { //if colliding
								if (e.getVelocity().y < 0) break;
								collided = true;
								float sampleX;
								float max, min;
								if (tileId == 1) { //left-to-right slope
									sampleX = colliderPos.x + collider.size.x;
									min = 0.f;
									max = 1.f;
								}
								else { //right-to-left slope
									sampleX = colliderPos.x;
									min = 1.f;
									max = 0.f;
								}

								if (sampleX >= tileX && sampleX <= tileX + layer.tileSize) { //check if the sample is in this tile
									float fraction = myMath::mapValue(sampleX, tileX, tileX + layer.tileSize, min, max);

									e.setPos(vec2(e.getPos().x, bottomTile - layer.tileSize * fraction - collider.size.y - collider.offset.y));
									grounded = true;
								}
							}	
						}
							break;
						case 0:
						case 2:
						{
							int tileX = j * layer.tileSize;
							int tileY = i * layer.tileSize;
							
							
							if (tileId == 0) {
								//if (collider.pos.y + collider.size.y > tileY + layer.tileSize * 0.05f) break;
								if (e.getVelocity().y < 0.0f) break;
								if (colliderPos.y + collider.size.y > tileY + layer.tileSize /2.f) break;
							}


							float leftTile = tileX;
							float rightTile = tileX + layer.tileSize;
							float topTile = tileY;
							float bottomTile = tileY + layer.tileSize;

							float overlapX = fminf(rightTile, colliderPos.x + collider.size.x) - fmaxf(leftTile, colliderPos.x);
							float overlapY = fminf(bottomTile, colliderPos.y + collider.size.y) - fmaxf(topTile, colliderPos.y);

							vec2 eCenter = vec2(colliderPos.x  + collider.size.x / 2, colliderPos.y + collider.size.y / 2);
							vec2 tCenter = vec2(tileX + layer.tileSize / 2, tileY + layer.tileSize / 2); //tile Center


							vec2 dir = vec2(eCenter.x < tCenter.x ? -1 : 1, eCenter.y < tCenter.y ? -1 : 1);

							if (overlapX > -0.01f && overlapY > -0.01f) {
								collided = true;

								if (overlapX < overlapY) {
									e.addToPos(vec2(overlapX * dir.x, 0));
								}
								else {
									e.addToPos(vec2(0, overlapY * dir.y));
									if (dir.y < 0) {
										grounded = true;
									}
									else {
										e.setVelocity(vec2(e.getVelocity().x, 0.01f));
									}
								}
							}
						}
							break;
						default:
							break;
					}
					
				}
			}
			
			e.setGrounded(grounded);

			return collided;
	}

	bool checkCollision(Collider& a, Collider& b){
		float leftA = a.pos.x + a.offset.x;
		float rightA = a.pos.x + + a.offset.x + a.size.x;
		float topA = a.pos.y + a.offset.y;
		float bottomA = a.pos.y + a.offset.y + a.size.y;
	
		float leftB = b.pos.x + b.offset.x;
		float rightB = b.pos.x + +b.offset.x + b.size.x;
		float topB = b.pos.y + b.offset.y;
		float bottomB = b.pos.y + b.offset.y + b.size.y;

		float overlapX = fminf(rightA, rightB) - fmaxf(leftA, leftB);
		float overlapY = fminf(bottomA, bottomB) - fmaxf(topA, topB);

		if (overlapX > -0.01f && overlapY > -0.01f) { //if colliding
			return true;
		}
		return false;
	}
} 