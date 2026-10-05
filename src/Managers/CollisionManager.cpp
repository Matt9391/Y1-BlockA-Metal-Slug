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
			vec2 startPos = vec2(static_cast<float>(static_cast<int>((e.getPos().x + collider.offset.x) / layer.tileSize)),
								 static_cast<float>(static_cast<int>((e.getPos().y + collider.offset.y) / layer.tileSize)));
			//vec2 endPosition = ; //bottom right
			vec2 endPos = vec2(static_cast<float>(static_cast<int>((e.getPos().x + collider.offset.x + e.getCollider().size.x) / layer.tileSize)),
							   static_cast<float>(static_cast<int>((e.getPos().y + collider.offset.y + e.getCollider().size.y) / layer.tileSize))); //bottom right
			//std::cout << "startX: " << startPos.x << "endX: " << endPos.x << std::endl;
			//std::cout << "startY: " << startPos.y << "endY: " << endPos.y << std::endl;

			bool grounded = false;
			bool collided = false;

			for (int i = static_cast<int>(startPos.y); i <= endPos.y; i++) {
				if (i < 0 || i >= layer.tiles.y)
					continue;
				for (int j = static_cast<int>(startPos.x); j <= endPos.x; j++) {
					if (j < 0 || j >= layer.tiles.x)
						continue;

					const vec2 colliderPos = (collider.pos + collider.offset); //recompile it everytime because it changes but since its not a reference it need to be recompiled
					//std::cout << i * static_cast<int>(layer.tiles.x) + j << std::endl;
					int tileId = layer.data[i * static_cast<int>(layer.tiles.x) + j] - layer.firstgid;
					if (tileId == -layer.firstgid) continue;
					
					vec2 currentTile = vec2(static_cast<float>(j * layer.tileSize),
											static_cast<float>( i * layer.tileSize));
					vec2 overlaps = checkOverlapMapCollision(collider, currentTile, layer.tileSize);

					switch (tileId)
					{
						case TileType::SLOPE_L_TO_R:
						case TileType::SLOPE_R_TO_L:
						{
						
							if (overlaps.x > -0.01f && overlaps.y > -0.01f) { //if colliding
								if (e.getVelocity().y < 0) break;
								collided = true;
								float sampleX;
								float max, min;
								if (tileId ==  TileType::SLOPE_L_TO_R) { //left-to-right slope
									sampleX = colliderPos.x + collider.size.x;
									min = 0.f;
									max = 1.f;
								}
								else { //right-to-left slope
									sampleX = colliderPos.x;
									min = 1.f;
									max = 0.f;
								}

								if (sampleX >= currentTile.x && sampleX <= currentTile.x + layer.tileSize) { //check if the sample is in this tile
									float fraction = myMath::mapValue(sampleX, currentTile.x, currentTile.x + layer.tileSize, min, max);
									e.setPos(vec2(e.getPos().x, currentTile.y + layer.tileSize - layer.tileSize * fraction - collider.size.y - collider.offset.y));
									grounded = true;
								}
							}	
						}
							break;
						case  TileType::BLOCK:
						case  TileType::PLATFORM:
						{
							if (tileId ==  TileType::PLATFORM) {
								//if (collider.pos.y + collider.size.y > tileY + layer.tileSize * 0.05f) break;
								if (e.getVelocity().y < 0.0f) break;
								if (colliderPos.y + collider.size.y > currentTile.y + layer.tileSize /2.f) break;
							}

							vec2 eCenter = vec2(colliderPos.x  + collider.size.x / 2.f, colliderPos.y + collider.size.y / 2.f);
							vec2 tCenter = vec2(currentTile.x + layer.tileSize / 2.f, currentTile.y + layer.tileSize / 2.f); //tile Center


							vec2 dir = vec2(eCenter.x < tCenter.x ? -1.f : 1.f, eCenter.y < tCenter.y ? -1.f : 1.f);

							if (overlaps.x > -0.01f && overlaps.y > -0.01f) {
								collided = true;

								if (overlaps.x < overlaps.y) {
									e.addToPos(vec2(overlaps.x * dir.x, 0));
								}
								else {
									e.addToPos(vec2(0, overlaps.y * dir.y));
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
		float rightA = a.pos.x + a.offset.x + a.size.x;
		float topA = a.pos.y + a.offset.y;
		float bottomA = a.pos.y + a.offset.y + a.size.y;
	
		float leftB = b.pos.x + b.offset.x;
		float rightB = b.pos.x + b.offset.x + b.size.x;
		float topB = b.pos.y + b.offset.y;
		float bottomB = b.pos.y + b.offset.y + b.size.y;

		float overlapX = fminf(rightA, rightB) - fmaxf(leftA, leftB);
		float overlapY = fminf(bottomA, bottomB) - fmaxf(topA, topB);

		if (overlapX > -0.01f && overlapY > -0.01f) { //if colliding
			return true;
		}
		return false;
	}


	vec2 checkOverlapMapCollision(Collider& collider,const vec2& tilePos,const int& tileSize) {
		const vec2 colliderPos = (collider.pos + collider.offset);
		float leftTile = tilePos.x;
		float rightTile = tilePos.x + tileSize;
		float topTile = tilePos.y;
		float bottomTile = tilePos.y + tileSize;

		float overlapX = fminf(rightTile, colliderPos.x + collider.size.x) - fmaxf(leftTile, colliderPos.x);
		float overlapY = fminf(bottomTile, colliderPos.y + collider.size.y) - fmaxf(topTile, colliderPos.y);

		return vec2(overlapX, overlapY);

	}

	bool checkMapCollision(Collider& collider, MapLayer& layer, int axis /* 0 = x, 1 = y, -1 = xy*/) {
		vec2 startPos = vec2(floorf((collider.pos.x + collider.offset.x) / layer.tileSize),
			floorf((collider.pos.y + collider.offset.y) / layer.tileSize));

		vec2 endPos = vec2(floorf((collider.pos.x + collider.offset.x + collider.size.x) / layer.tileSize),
						   floorf((collider.pos.y + collider.offset.y + collider.size.y) / layer.tileSize)); //bottom right

		bool collided = false;

		for (int i = static_cast<int>(startPos.y); i <= endPos.y; i++) {
			if (i < 0 || i >= layer.tiles.y)
				continue;
			for (int j = static_cast<int>(startPos.x); j <= endPos.x; j++) {
				if (j < 0 || j >= layer.tiles.x)
					continue;

				const vec2 colliderPos = (collider.pos + collider.offset); //recompile it everytime because it changes but since its not a reference it need to be recompiled
				
				int tileId = layer.data[i * static_cast<int>(layer.tiles.x) + j] - layer.firstgid;
				if (tileId == -layer.firstgid) continue;

				switch (tileId)
				{
					case 2:
					{
						int tileX = j * layer.tileSize;
						int tileY = i * layer.tileSize;

						float leftTile  = static_cast<float>(tileX);
						float rightTile = static_cast<float>(tileX + layer.tileSize);
						float topTile   = static_cast<float>(tileY);
						float bottomTile= static_cast<float>(tileY + layer.tileSize);

						float overlapX = fminf(rightTile, colliderPos.x + collider.size.x) - fmaxf(leftTile, colliderPos.x);
						float overlapY = fminf(bottomTile, colliderPos.y + collider.size.y) - fmaxf(topTile, colliderPos.y);

						vec2 eCenter = vec2(colliderPos.x + collider.size.x / 2.f, colliderPos.y + collider.size.y / 2.f);
						vec2 tCenter = vec2(static_cast<float>(tileX + layer.tileSize / 2.f), static_cast<float>(tileY + layer.tileSize / 2.f)); //tile Center

						if (overlapX > -0.01f && overlapY > -0.01f) {

							if (axis == -1) {
								collided = true;
							}
							else {

								if (overlapX < overlapY) {
									if (axis == 0) {
										collided = true;
									}
								}
								else {
									if (axis == 1) {
										collided = true;
									}
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

		return collided;
	}


	// TODO: PIXEL-PERFECT COLLISION
} 