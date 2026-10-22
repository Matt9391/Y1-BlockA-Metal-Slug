#include "precomp.h"
#include "CollisionManager.h"
#include <iostream>
#include <Entity.h>
#include <Collider.h>
#include <ResourceManager.h>
#include <myMath.h>


namespace CollisionManager {

	bool resolveMapCollision(Entity& e, const MapLayer& layer) {
		const Collider& collider = e.getCollider();
		vec2 startPos = vec2(static_cast<float>(static_cast<int>((e.getPos().x + collider.offset.x) / layer.tileSize)),
								static_cast<float>(static_cast<int>((e.getPos().y + collider.offset.y) / layer.tileSize)));
		//vec2 endPosition = ; //bottom right
		vec2 endPos = vec2(static_cast<float>(static_cast<int>((e.getPos().x + collider.offset.x + e.getCollider().size.x) / layer.tileSize)),
							static_cast<float>(static_cast<int>((e.getPos().y + collider.offset.y + e.getCollider().size.y) / layer.tileSize))); //bottom right

		bool grounded = false;
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

	bool checkCollision(const Collider& a,const Collider& b, const ResourceManager& rsm, int depth){ //TODO: add enum to show actualy collision type
		bool result = false;

		result = checkRadiusCollision(a,b); //* Distance Squared check BROAD BROAD PHASE

		if(!result) return result;
		if(depth == 0) return result;

		result = false;
		const vec2 overlaps = getCollisionOverlap(a,b); //* AABB BROAD PHASE
		if (overlaps.x > -0.01f && overlaps.y > -0.01f) { //if colliding
			result = true;
		}
		
		if(!result) return result;
		if(depth == 1) return result;
		
		result = checkPixelPerfectCollision(a,b,rsm); //* NARROW PHASE
		
		return result;
	}

	bool resolveCollisionAOverB(Entity& e, const Collider& b){
		vec2 overlaps = getCollisionOverlap(e.getCollider(), b);
		bool grounded = false;
		bool collided = false;

		const vec2 colliderPosA = (e.getCollider().pos + e.getCollider().offset);
		const vec2 colliderPosB = (b.pos + b.offset);
		vec2 eCenter = vec2(colliderPosA.x  + e.getCollider().size.x / 2.f, colliderPosA.y + e.getCollider().size.y / 2.f);
		vec2 bCenter = vec2(colliderPosB.x + b.size.x / 2.f, colliderPosB.y + b.size.y / 2.f); //tile Center


		vec2 dir = vec2(eCenter.x < bCenter.x ? -1.f : 1.f, eCenter.y < bCenter.y ? -1.f : 1.f);


		if (overlaps.x > -0.01f && overlaps.y > -0.01f) {
			collided = true;
			if (overlaps.x < overlaps.y) {
				e.addToPos(vec2(overlaps.x * dir.x, 0));
			}
			else {
				e.addToPos(vec2(0, overlaps.y * dir.y));
				if (dir.y < 0) {
					grounded = true;
					e.setGrounded(grounded);
				}
				else {
					e.setVelocity(vec2(e.getVelocity().x, 0.01f));
				}
			}

		}


		return collided;
	}
	
	bool checkRadiusCollision(const Collider& a, const Collider& b){
		const vec2 aPos = a.pos + a.offset + (a.size / 2.f);
		const vec2 bPos = b.pos + b.offset + (b.size / 2.f);
		const float radiusSum = a.radius + b.radius;

		return myMath::DistanceSquared(aPos, bPos) < radiusSum * radiusSum;
	}


	
	vec2 getCollisionOverlap(const Collider& a,const Collider& b){
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

		return vec2(overlapX,overlapY);
	}

	vec2 checkOverlapMapCollision(const Collider& collider,const vec2& tilePos,const int& tileSize) {
		const vec2 colliderPos = (collider.pos + collider.offset);
		float leftTile = tilePos.x;
		float rightTile = tilePos.x + tileSize;
		float topTile = tilePos.y;
		float bottomTile = tilePos.y + tileSize;

		float overlapX = fminf(rightTile, colliderPos.x + collider.size.x) - fmaxf(leftTile, colliderPos.x);
		float overlapY = fminf(bottomTile, colliderPos.y + collider.size.y) - fmaxf(topTile, colliderPos.y);

		return vec2(overlapX, overlapY);

	}

	bool checkMapCollision(const Collider& collider, const MapLayer& layer, const int axis /* 0 = x, 1 = y, -1 = xy*/) {
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

	// DONE: PIXEL-PERFECT COLLISION
	// add resourceId AND current Frame to collider so I can then ask from the resourceManager for the sprite and then do the collision
	bool checkPixelPerfectCollision(const Collider& a, const Collider& b, const ResourceManager& rsm){
		const vec2 overlaps = getCollisionOverlap(a,b);
		const int ow = (int)overlaps.x;
		const int oh = (int)overlaps.y;
		if (ow <= 0 || oh <= 0) return false;

		// world-space top-left of each collider
		const float aL = (int)(a.pos.x + a.offset.x), aT = (int)(a.pos.y + a.offset.y);
		const float bL = (int)(b.pos.x + b.offset.x), bT = (int)(b.pos.y + b.offset.y);
		const int startX = static_cast<int>(fmaxf(aL, bL));
		const int startY = static_cast<int>(fmaxf(aT, bT));

		for(int i = 0; i < a.layerCount; i++){
			const int aSpriteX = (int)(a.pos.x + a.spriteOffset[i].x);
			const int aSpriteY = (int)(a.pos.y + a.spriteOffset[i].y);
			
			for(int j = 0; j < b.layerCount; j++){
				const int bSpriteX = (int)(b.pos.x + b.spriteOffset[j].x);
				const int bSpriteY = (int)(b.pos.y + b.spriteOffset[j].y);

				Sprite* sA = rsm.getSprite(a.id[i]);
				Sprite* sB = rsm.getSprite(b.id[j]);

				if(sA == nullptr || sB == nullptr) continue;

				const int aStartX = startX - aSpriteX, aStartY = startY - aSpriteY;
				const int bStartX = startX - bSpriteX, bStartY = startY - bSpriteY;


				const int wA = sA->GetWidth(), wB = sB->GetWidth();
				const int hA = sA->GetHeight(), hB = sB->GetHeight();
				const int pitchA = wA * sA->Frames(); // frames are laid out side by side
				const int pitchB = wB * sB->Frames();

				// move to the right frame once, outside the pixel loops
				const uint* bufA = a.flipped ? sA->GetReverseBuffer() : sA->GetBuffer();
				const uint* bufB = b.flipped ? sB->GetReverseBuffer() : sB->GetBuffer();

				const uint* pxA = bufA + a.frame[i] * wA;
				const uint* pxB = bufB + b.frame[j] * wB;

				// loop from 0 to the overlap value
				for (int y = 0; y < oh; y++) {
					const int ay = aStartY + y;
					const int by = bStartY + y;
					if (ay < 0 || ay >= hA || by < 0 || by >= hB) continue;

					// loop from 0 to the overlap value	
					for (int x = 0; x < ow; x++) {
						const int ax = aStartX + x;
						const int bx = bStartX + x;
						if (ax < 0 || ax >= wA || bx < 0 || bx >= wB) continue;

						const uint pA = pxA[ax + ay * pitchA];
						const uint pB = pxB[bx + by * pitchB];

						if ((pA & 0xFFffffff) && (pB & 0xFFffffff)) return true; // both non-transparent
					}
				}

			}
		}

		return false;
	}
	

	
} 