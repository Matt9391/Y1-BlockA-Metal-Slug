#include "precomp.h"
#include "Renderer.h"
#include <ResourceManager.h>
#include <HUDText.h>
#include <iostream>
#include <Spawner.h>

void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y);

Renderer::Renderer() :
	renderSetCount(0),
	collidersCount(0),
	textsCount(0),
	spriteSetCount(0),
	colliders{nullptr},
	printer(),
	mapRenderSet{nullptr}
	{}

Renderer::~Renderer(){
	mapRenderSet = nullptr;
	for(int i = 0; i < MAXCOLLIDERS; i++){
		colliders[i] = nullptr;
	}
}

void Renderer::reset(){
	mapRenderSet = nullptr;
	for(int i = 0; i < MAXCOLLIDERS; i++){
		colliders[i] = nullptr;
	}
}


void Renderer::addCollider(const Collider& c) {
	if (collidersCount == MAXCOLLIDERS)
		throw runtime_error("Max colliders reached");
	colliders[collidersCount++] = &c;
}


void Renderer::addRenderSet(RenderSet rs) {
	if (renderSetCount == MAXRENDERSETS)
		throw runtime_error("Max render sets reached");
	renderSets[renderSetCount++] = rs;
	
}

void Renderer::addMapRenderSet(const MapRenderSet& mrs) {
	mapRenderSet = &mrs;
}

void Renderer::addHUDText(HUDText t) {
	if (textsCount == MAXTEXTS)
		throw runtime_error("Max texts reached");
	texts[textsCount++] = t;
}

void Renderer::addSpriteSet(SpriteSet ss) {
	if (spriteSetCount == MAXSPRITESETS)
		throw runtime_error("Max sprite sets reached");

	spriteSets[spriteSetCount++] = ss;
}

void Renderer::clearColliders() {
	for (int i = 0; i < MAXCOLLIDERS; i++) {
		colliders[i] = nullptr;
	}
	collidersCount = 0;
}

void Renderer::clearRenderSets() {
	for (int i = 0; i < MAXRENDERSETS; i++) {
		renderSets[i] = RenderSet();
	}
	renderSetCount = 0;
}

void Renderer::clearTexts() {
	for (int i = 0; i < MAXTEXTS; i++) {
		texts[i] = HUDText();
	}
	textsCount = 0;
}

void Renderer::clearSpriteSets() {
	for (int i = 0; i < MAXSPRITESETS; i++) {
		spriteSets[i] = SpriteSet();
	}
	spriteSetCount = 0;
}
void Renderer::render(Surface* screen, const ResourceManager& resourceManager, const vec2& cameraOffset) {
	
	if (mapRenderSet != nullptr) {
		
		for (int i = 0; i < mapRenderSet->layerCount; i++) {
			//for (int i = 0; i < mapRenderSet.layerCount - 2; i++) { //uncomment to remove hitboxes
			const MapLayer& layer = mapRenderSet->layers[i];
			
			const int& tileSize = mapRenderSet->tileSize;

			int startX = static_cast<int>(fmaxf(floorf(cameraOffset.x) / tileSize, 0.f));
			int startY = static_cast<int>(fmaxf(floorf(cameraOffset.y) / tileSize, 0.f));

			int endX = startX + (SCRWIDTH / tileSize) + 1;
			int endY = startY + (SCRHEIGHT / tileSize) + 1;

			//don't go outside the map
			endX = static_cast<int>(fminf(static_cast<float>(endX),layer.tiles.x));
			endY = static_cast<int>(fminf(static_cast<float>(endY),layer.tiles.y));
		
			int count = 0;
		
			for (int y = startY; y < endY; y++) {
				for (int x = startX; x < endX; x++) {
					count++;
					int tileId = layer.data[y * static_cast<int>(layer.tiles.x) + x];
					if (tileId == 0) continue; // empty tile, nothing to draw


					int localId = tileId - layer.firstgid;
					int srcCol = localId % static_cast<int>(layer.tiles.x);
					int srcRow = localId / static_cast<int>(layer.tiles.x);

					int destX = static_cast<int>(mapRenderSet->pos.x + x * 8);
					int destY = static_cast<int>(mapRenderSet->pos.y + y * 8);

					drawTile(mapRenderSet->tileSize,
							srcCol,
							srcRow, 
							screen, 
							resourceManager.getSprite(layer.resourceId)->GetSurface(), 
							static_cast<int>(destX - cameraOffset.x), 
							static_cast<int>(destY - cameraOffset.y));

				}
			}
			printf("%d\n", count);
		}
	}
	for (int i = 0; i < renderSetCount; i++) {
		RenderSet& rs = this->renderSets[i];
		bool flipped = rs.animationSet.flipped;
		for (int j = 0; j < rs.animationSet.layerCount; j++) {
			AnimationLayer& layer = rs.animationSet.layers[j];
			Sprite* sprite = resourceManager.getSprite(layer.resourceId);
			if (sprite == nullptr) continue;
			vec2& offset = flipped ? layer.offsetFlipped : layer.offset;

			sprite->SetFrame(layer.currentFrame);
			//sprite->Draw(screen, rs.pos.x + layer.offset.x, rs.pos.y + layer.offset.y);
			//sprite->Draw(screen, rs.pos.x + layer.offset.x - cameraOffset.x, rs.pos.y + layer.offset.y - cameraOffset.y, true);
			int scale = 1;
			sprite->DrawScaled(screen, static_cast<int>(rs.pos.x + offset.x * scale - cameraOffset.x), 
				static_cast<int>(rs.pos.y + offset.y * scale - cameraOffset.y), scale, flipped);
		}

	}

	if (mapRenderSet != nullptr) {
		for (int i = 2; i < mapRenderSet->layerCount - 1; i++) {
			const MapLayer& layer = mapRenderSet->layers[i];
			for (int y = 0; y < static_cast<int>(layer.tiles.y); y++) {
				for (int x = 0; x < static_cast<int>(layer.tiles.x); x++) {
					int tileId = layer.data[y * static_cast<int>(layer.tiles.x) + x];
					if (tileId == 0) continue; // empty tile, nothing to draw

					int localId = tileId - layer.firstgid;
					int srcCol = localId % static_cast<int>(layer.tiles.x);
					int srcRow = localId / static_cast<int>(layer.tiles.x);

					int destX = static_cast<int>(mapRenderSet->pos.x + x * 8);
					int destY = static_cast<int>(mapRenderSet->pos.y + y * 8);

					drawTile(mapRenderSet->tileSize,
							srcCol,
							srcRow, 
							screen, 
							resourceManager.getSprite(layer.resourceId)->GetSurface(), 
							static_cast<int>(destX - cameraOffset.x), 
							static_cast<int>(destY - cameraOffset.y));
				}
			}
		}
	}

	if (mapRenderSet != nullptr) {
		for (int i = 0; i < mapRenderSet->layerObjCount; i++) {
			//for (int i = 0; i < mapRenderSet.layerCount - 1; i++) { //uncomment to remove hitboxes
			for (int j = 0; j < mapRenderSet->spawnerCounts[i]; j++) {
				const Spawner* spawner = mapRenderSet->spawners[i][j];

				const vec2& pos = spawner->getPos();
				const vec2& size = spawner->getSize();

				screen->Box(static_cast<int>(pos.x - cameraOffset.x), 
							static_cast<int>(pos.y - cameraOffset.y),
							static_cast<int>(pos.x - cameraOffset.x + size.x), 
							static_cast<int>(pos.y - cameraOffset.y + size.y), 
							0xFFFF00);
			}
		}
	}

	for (int i = 0; i < collidersCount; i++) {
		const Collider* c = colliders[i];
		if(!c) continue;
		screen->Box(static_cast<int>(c->pos.x + c->offset.x - cameraOffset.x), 
					static_cast<int>(c->pos.y + c->offset.y - cameraOffset.y),
					static_cast<int>(c->pos.x + c->offset.x - cameraOffset.x + c->size.x), 
					static_cast<int>(c->pos.y + c->offset.y - cameraOffset.y + c->size.y), 
					0xFF0000);
	}

	for (int i = 0; i < spriteSetCount; i++) {
		SpriteSet& ss = spriteSets[i];
		Sprite* sprite = resourceManager.getSprite(ss.resourceId);
		if (sprite == nullptr) continue;

		sprite->Draw(screen, static_cast<int>(ss.pos.x), static_cast<int>(ss.pos.y), 0);
	}

	for (int i = 0; i < textsCount; i++) {
		HUDText& t = texts[i];
		Surface* s = resourceManager.getSprite(t.resourceId)->GetSurface();
		printer.drawText(t, s, screen);
	}

	
}


void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y) {

	//check if the tile is outside the screen
	if (x + tileSize < 0 || y + tileSize < 0 || x > screen->width || y > screen->height)
		return;

	//check for void pixel, I chose 'gg' and 'aj' as void pixel based on the tilesetGuide
	//if ((tx + 'a' == this->voidChar[0]) && (ty + 'a' == this->voidChar[1]))
	//	return;

	//clip position and size if the tile is partially outside the screen
	int dx = 0, dy = 0;
	int maxX = tileSize, maxY = tileSize;

	//set clipping values
	if (x < 0) dx = -x;
	if (y < 0) dy = -y;
	if (x + tileSize > screen->width)  maxX = screen->width - x;
	if (y + tileSize > screen->height) maxY = screen->height - y;

	//get pointers to the source tile and destination on screen
	uint* source = tileset->pixels + tx * tileSize + (ty * tileSize) * tileset->width;
	//add the clipping offsets
	source += dy * tileset->width;
	//set destination on screen with clipping offsets
	uint* destination = screen->pixels + x + (y + dy) * screen->width;

	//"transparent" pixel value, actually its magenta because it's easy to visualize in photoshop
	const uint transparent = 0x00FFFFFF;

	//for each pixel in the tile area
	for (int i = dy; i < maxY; i++) {
		for (int j = dx; j < maxX; j++) {
			//if the pixel is not "transparent" copy it to the screen
			if (source[j] != transparent)
				destination[j] = source[j];
		}

		//then move to the next row
		source += tileset->width;
		destination += screen->width;
	}
}