// Renderer - collects everything to draw during the frame (render datas, map, parallax, HUD texts,
// sprite sets) and draws it all in render(). The scenes fill and clear it.
#pragma once

#include <RenderData.h>
#include <MapRenderData.h>
#include <ParallaxRenderData.h>
#include <ResourceManager.h>
#include <Collider.h>
#include <Printer.h>
#include <HUDText.h>
#include <SpriteSet.h>

class Tmpl8::Surface;

class Renderer {
public:
	Renderer();
	~Renderer();

	void reset();

	void addCollider(const Collider& c);
	void addRenderData(RenderData rs);
	void addHUDText(HUDText t);
	
	void addSpriteSet(SpriteSet ss);
	void addMapRenderData(const MapRenderData& mrd);
	void addParallaxRenderData(const ParallaxRenderData& prd);

	void clearRenderDatas();
	void clearParallaxRenderData();
	void clearColliders();
	void clearTexts();

	void clearSpriteSets();

	void render(Surface* screen, const ResourceManager& resourceManager, const vec2& cameraOffset);

	void setDarkOverlay(bool darkOverlay_); // halve the brightness of everything drawn before the HUD (used on the win screen)
private:
	static const int MAXRENDERSETS = 100; //REMBEMBER THAT THEY FINISH FAST
	static const int MAXRENDERLAYERS = 4;
	static const int MAXCOLLIDERS = 100;
	static const int MAXTEXTS = 100;
	static const int MAXSPRITESETS = 100;
	
	RenderData renderDatas[MAXRENDERLAYERS][MAXRENDERSETS]; // one list per render layer
	const MapRenderData* mapRenderData;
	const ParallaxRenderData* parallaxRenderData;
	const Collider* colliders[MAXCOLLIDERS]; // pointers only, for debug drawing
	HUDText texts[MAXTEXTS];
	SpriteSet spriteSets[MAXSPRITESETS];
	
	int renderDataCount[MAXRENDERLAYERS];
	int collidersCount;
	int textsCount;
	int spriteSetCount;

	bool darkOverlay;
	bool crtEffect; // scanlines + a slight colour fringe over the whole screen

	Printer printer;

	void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y); // copy one tile from a tileset to the screen, with clipping

};