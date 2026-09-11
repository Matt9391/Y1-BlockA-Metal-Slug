#include "precomp.h"
#include "Renderer.h"
#include <ResourceManager.h>
#include <iostream>

void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y);

Renderer::Renderer() :
	renderSetCount(0)
	{}

void Renderer::addRenderSet(RenderSet rs) {
	renderSets[renderSetCount++] = rs;
	
}
void Renderer::addMapRenderSet(const MapRenderSet& mrs) {
	mapRenderSet = mrs;
}

void Renderer::clearRenderSets() {
	for (int i = 0; i < MAXRENDERSETS; i++) {
		renderSets[i] = RenderSet();
	}
	renderSetCount = 0;
}

void Renderer::render(Surface* screen, const ResourceManager& resourceManager, const vec2& cameraOffset) {

	for (int i = 0; i < mapRenderSet.layerCount; i++) {
		MapLayer& layer = mapRenderSet.layers[i];
		for (int y = 0; y < layer.tiles.y; y++) {
			for (int x = 0; x < layer.tiles.x; x++) {
				int tileId = layer.data[y * static_cast<int>(layer.tiles.x) + x];
				if (tileId == 0) continue; // empty tile, nothing to draw

				int localId = tileId - layer.firstgid;
				int srcCol = localId % static_cast<int>(layer.tiles.x);
				int srcRow = localId / layer.tiles.x;

				int destX = mapRenderSet.pos.x + x * 8;
				int destY = mapRenderSet.pos.y + y * 8;

				drawTile(mapRenderSet.tileSize, srcCol, srcRow, screen, resourceManager.getSprite(layer.resourceId)->GetSurface(), destX - cameraOffset.x, destY - cameraOffset.y);

			}
		}
	}

	for (int i = 0; i < renderSetCount; i++) {
		RenderSet& rs = this->renderSets[i];

		for (int j = 0; j < rs.animationSet.layerCount; j++) {
			AnimationLayer& layer = rs.animationSet.layers[j];
			Sprite* sprite = resourceManager.getSprite(layer.resourceId);

			sprite->SetFrame(layer.currentFrame);
			//sprite->Draw(screen, rs.pos.x + layer.offset.x, rs.pos.y + layer.offset.y);
			//sprite->Draw(screen, rs.pos.x + layer.offset.x - cameraOffset.x, rs.pos.y + layer.offset.y - cameraOffset.y, true);
			sprite->DrawScaled(screen, rs.pos.x + layer.offset.x - cameraOffset.x, rs.pos.y + layer.offset.y - cameraOffset.y, 6, true);
		}

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
	const uint transparent = 0xFFFF00FF;

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