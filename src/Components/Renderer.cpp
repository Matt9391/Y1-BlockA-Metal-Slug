#include "precomp.h"
#include "Renderer.h"
#include <ResourceManager.h>
#include <HUDText.h>
#include <iostream>
#include <Spawner.h>
#include <myMath.h>



Renderer::Renderer() :
	renderDataCount{0},
	collidersCount(0),
	textsCount(0),
	spriteSetCount(0),
	colliders{nullptr},
	printer(),
	mapRenderData{nullptr},
	parallaxRenderData{nullptr},
	darkOverlay(false),
	crtEffect(true)
	{}

Renderer::~Renderer(){
	mapRenderData = nullptr;
	for(int i = 0; i < MAXCOLLIDERS; i++){
		colliders[i] = nullptr;
	}
}

void Renderer::reset(){
	mapRenderData = nullptr;
	for(int i = 0; i < MAXCOLLIDERS; i++){
		colliders[i] = nullptr;
	}
}


void Renderer::addCollider(const Collider& c) {
	if (collidersCount == MAXCOLLIDERS){
		printf("Max colliders reached");
		return;
	}
	colliders[collidersCount++] = &c;
}


void Renderer::addRenderData(RenderData rs) {
	if (renderDataCount[rs.layer] == MAXRENDERSETS){
		printf("Max render sets reache on layer: %d", rs.layer);
		return;
	}
	renderDatas[rs.layer][renderDataCount[rs.layer]++] = rs;
	
}

void Renderer::addMapRenderData(const MapRenderData& mrd) {
	mapRenderData = &mrd;
}

void Renderer::addParallaxRenderData(const ParallaxRenderData& prd){
	parallaxRenderData = &prd;
}


void Renderer::addHUDText(HUDText t) {
	if (textsCount == MAXTEXTS){
		printf("Max texts reached");
		return;
	}
	texts[textsCount++] = t;
}

void Renderer::addSpriteSet(SpriteSet ss) {
	if (spriteSetCount == MAXSPRITESETS){
		printf("Max sprite sets reached");
		return;
	}

	spriteSets[spriteSetCount++] = ss;
}

void Renderer::clearColliders() {
	for (int i = 0; i < collidersCount; i++) { 
		colliders[i] = nullptr; 
	}
	collidersCount = 0;
}

void Renderer::clearRenderDatas() {
	for (int j = 0; j < MAXRENDERLAYERS; j++) {
		for (int i = 0; i < MAXRENDERSETS; i++) {
			renderDatas[j][i] = RenderData();
		}
		renderDataCount[j] = 0;
	}
}

void Renderer::clearParallaxRenderData() {
	parallaxRenderData = nullptr;
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

void Renderer::setDarkOverlay(bool darkOverlay_){
	this->darkOverlay = darkOverlay_;
}
void Renderer::render(Surface* screen, const ResourceManager& resourceManager, const vec2& cameraOffset) {
	if(parallaxRenderData != nullptr){
		const ParallaxRenderData& p = *parallaxRenderData;
		Sprite* sprite = resourceManager.getSprite(p.resourceId);
		if (sprite){
			sprite->Draw(screen, 
						 static_cast<int>(p.pos.x - cameraOffset.x * p.parallaxFactor),
						 static_cast<int>(p.pos.y - cameraOffset.y * p.parallaxFactor), 
						 0);
			
			
			
		}
	}


	if (mapRenderData != nullptr) {
		const int& tileSize = mapRenderData->tileSize;

		int startX = static_cast<int>(fmaxf(floorf(cameraOffset.x) / tileSize, 0.f));
		int startY = static_cast<int>(fmaxf(floorf(cameraOffset.y) / tileSize, 0.f));

		int endX = startX + (SCRWIDTH / tileSize) + 1;
		int endY = startY + (SCRHEIGHT / tileSize) + 1;

		//don't go outside the map													//each layer has the same tile number
		endX = static_cast<int>(fminf(static_cast<float>(endX), mapRenderData->layers[0].tiles.x));
		endY = static_cast<int>(fminf(static_cast<float>(endY), mapRenderData->layers[0].tiles.y));

		// for (int i = 0; i < mapRenderData->layerCount; i++) {
			for (int i = 0; i < mapRenderData->layerCount - 2; i++) { //uncomment to remove hitboxes
			const MapLayer& layer = mapRenderData->layers[i];
			
			Sprite* sprite = resourceManager.getSprite(layer.resourceId);
			if (!sprite) continue;
			Surface* tilesetSurf = sprite->GetSurface();
		
			for (int y = startY; y < endY; y++) {
				for (int x = startX; x < endX; x++) {
					int tileId = layer.data[y * static_cast<int>(layer.tiles.x) + x];
					if (tileId == 0) continue; // empty tile, nothing to draw


					int localId = tileId - layer.firstgid;
					int srcCol = localId % static_cast<int>(layer.tiles.x);
					int srcRow = localId / static_cast<int>(layer.tiles.x);

					int destX = static_cast<int>(mapRenderData->pos.x + x * 8);
					int destY = static_cast<int>(mapRenderData->pos.y + y * 8);

					drawTile(mapRenderData->tileSize,
							srcCol,
							srcRow, 
							screen, 
							tilesetSurf, 
							static_cast<int>(destX - cameraOffset.x), 
							static_cast<int>(destY - cameraOffset.y));

				}
			}
		}
	}
	for(int g = 0; g < MAXRENDERLAYERS; g++){

		for (int i = 0; i < renderDataCount[g]; i++) {
			
			RenderData& rs = this->renderDatas[g][i];
			bool flipped = rs.animationSet.flipped;
			
			for (int j = 0; j < rs.animationSet.layerCount; j++) {

				AnimationLayer& layer = rs.animationSet.layers[j];
				Sprite* sprite = resourceManager.getSprite(layer.resourceId);
			
				if (sprite == nullptr) continue;
				vec2& offset = flipped ? layer.offsetFlipped : layer.offset;
				
				sprite->SetFrame(layer.currentFrame);
				int scale = 1;
				sprite->DrawScaled(screen,
								  static_cast<int>(rs.pos.x + offset.x * scale - cameraOffset.x), 
								  static_cast<int>(rs.pos.y + offset.y * scale - cameraOffset.y), 
								  scale, 
								  flipped);
			}
			
		}
	}
		
	if (mapRenderData != nullptr) {
		const int& tileSize = mapRenderData->tileSize;
			
		int startX = static_cast<int>(fmaxf(floorf(cameraOffset.x) / tileSize, 0.f));
		int startY = static_cast<int>(fmaxf(floorf(cameraOffset.y) / tileSize, 0.f));

		int endX = startX + (SCRWIDTH / tileSize) + 1;
		int endY = startY + (SCRHEIGHT / tileSize) + 1;

		//don't go outside the map													//each layer has the same tile number
		endX = static_cast<int>(fminf(static_cast<float>(endX), mapRenderData->layers[0].tiles.x));
		endY = static_cast<int>(fminf(static_cast<float>(endY), mapRenderData->layers[0].tiles.y));

		for (int i = 3; i < mapRenderData->layerCount - 1; i++) {
			const MapLayer& layer = mapRenderData->layers[i];

			Sprite* sprite = resourceManager.getSprite(layer.resourceId);
			if (!sprite) continue;
			Surface* tilesetSurf = sprite->GetSurface();

			for (int y = startY; y < endY; y++) {
				for (int x = startX; x < endX; x++) {
					int tileId = layer.data[y * static_cast<int>(layer.tiles.x) + x];
					if (tileId == 0) continue; // empty tile, nothing to draw

					int localId = tileId - layer.firstgid;
					int srcCol = localId % static_cast<int>(layer.tiles.x);
					int srcRow = localId / static_cast<int>(layer.tiles.x);

					int destX = static_cast<int>(mapRenderData->pos.x + x * 8);
					int destY = static_cast<int>(mapRenderData->pos.y + y * 8);

					drawTile(mapRenderData->tileSize,
							srcCol,
							srcRow, 
							screen, 
							tilesetSurf,
							static_cast<int>(destX - cameraOffset.x), 
							static_cast<int>(destY - cameraOffset.y));
				}
			}
		}
	}

	// if (mapRenderData != nullptr) {
	// 	for (int i = 0; i < mapRenderData->layerObjCount - 1; i++) {
	// 		//for (int i = 0; i < mapRenderData.layerCount - 1; i++) { //uncomment to remove hitboxes
	// 		for (int j = 0; j < mapRenderData->spawnerCounts[i]; j++) {
	// 			const Spawner* spawner = mapRenderData->spawners[i][j];

	// 			const vec2& pos = spawner->getPos();
	// 			const vec2& size = spawner->getSize();

	// 			screen->Box(static_cast<int>(pos.x - cameraOffset.x), 
	// 						static_cast<int>(pos.y - cameraOffset.y),
	// 						static_cast<int>(pos.x - cameraOffset.x + size.x), 
	// 						static_cast<int>(pos.y - cameraOffset.y + size.y), 
	// 						0xFFFF00);
	// 		}
	// 	}
	// }

	// const float angleIncr = 1;
	// for (int i = 0; i < collidersCount; i++) {
	// 	const Collider* c = colliders[i];
	// 	if(!c) continue;
	// 	screen->Box(static_cast<int>(c->pos.x + c->offset.x - cameraOffset.x), 
	// 				static_cast<int>(c->pos.y + c->offset.y - cameraOffset.y),
	// 				static_cast<int>(c->pos.x + c->offset.x - cameraOffset.x + c->size.x), 
	// 				static_cast<int>(c->pos.y + c->offset.y - cameraOffset.y + c->size.y), 
	// 				0xFF0000);

	// 	float angle = 0;
	// 	for(int j = 0; j < 360; j++){
	// 		vec2 pos = (
	// 			c->pos + c->offset + c->size / 2
	// 		);
	// 		screen->Plot(pos.x + cos(angle) * c->radius - cameraOffset.x, pos.y + sin(angle) * c->radius - cameraOffset.y, 0xFFff0000);
	// 		angle += angleIncr;
	// 	}

	// }
	
		


	if(darkOverlay){
		int end = screen->width * screen->height;
		for(int i = 0; i < end; i++){
			uint pixel = screen->pixels[i];

			uint alpha = pixel & 0xFF000000;
			uint red   = ((pixel & 0x00FF0000) >> 16) / 2;
			uint green = ((pixel & 0x0000FF00) >> 8) / 2;
	        uint blue  = (pixel & 0x000000FF) / 2;

			screen->pixels[i] = alpha | (red << 16) | (green << 8) | blue;
		}
	}

	for (int i = 0; i < spriteSetCount; i++) {
		SpriteSet& ss = spriteSets[i];
		Sprite* sprite = resourceManager.getSprite(ss.resourceId);
		if (sprite == nullptr) continue;

		sprite->SetFrame(ss.currentFrame);

		sprite->Draw(screen, static_cast<int>(ss.pos.x), static_cast<int>(ss.pos.y), 0);
	}

	for (int i = 0; i < textsCount; i++) {
		HUDText& t = texts[i];
		Surface* s = resourceManager.getSprite(t.resourceId)->GetSurface();
		printer.drawText(t, s, screen);
	}

	if (crtEffect) {
		for (int y = 0; y < screen->height; y++) {
			// Darken every other row
			if (y % 2 == 0) {
				for (int x = 0; x < screen->width; x++) {
					int i = y * screen->width + x;

					uint pixel = screen->pixels[i];

					uint alpha = pixel & 0xFF000000;
					uint red   = ((pixel & 0x00FF0000) >> 16) * 14 / 16;
					uint green = ((pixel & 0x0000FF00) >> 8) * 14 / 16;
					uint blue  = (pixel & 0x000000FF) * 14 / 16;

					screen->pixels[i] = alpha | (red << 16)| (green << 8) | blue;
				}
			}
		}

		uint newPixels[ SCRWIDTH * SCRHEIGHT];
		for (int y = 0; y < screen->height; y++) {
			// Darken every other row
			for (int x = 0; x < screen->width; x++) {
				int shift = 1; // how many pixels to offset — tune this, even 1 is often visible at this resolution

				int xRed  = myMath::constrain(x - shift, 0.f, screen->width);  // sample red from slightly left
				int xBlue = myMath::constrain(x + shift, 0.f, screen->width);  // sample blue from slightly right
				// int yRed  = myMath::constrain(y - shift, 0.f, screen->height);  // sample red from slightly left
				// int yBlue = myMath::constrain(y + shift, 0.f, screen->height);  // sample blue from slightly right
				int yRed  = y;  
				int yBlue = y;

				uint redPixel   = screen->pixels[yRed * screen->width + xRed];
				uint greenPixel = screen->pixels[y * screen->width + x];       // unshifted
				uint bluePixel  = screen->pixels[yBlue * screen->width + xBlue];

				uint red   = (redPixel   & 0x00FF0000);  // keep red's red channel only
				uint green = (greenPixel & 0x0000FF00);  // keep green's green channel only
				uint blue  = (bluePixel  & 0x000000FF);  // keep blue's blue channel only
				uint alpha = (greenPixel & 0xFF000000);  // alpha from center sample is fine
				
				newPixels[y * screen->width + x] = alpha | red | green | blue;
			}
		}

		for (int y = 0; y < screen->height; y++)
			for (int x = 0; x < screen->width; x++)
				screen->pixels[y * screen->width + x] = newPixels[y * screen->width + x];

		
	}	

}


void Renderer::drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y) {

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