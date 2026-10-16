#pragma once

#include <RenderData.h>
#include <MapRenderData.h>
#include <ParallaxRenderData.h>
#include <ResourceManager.h>
#include <Collider.h>
#include <Printer.h>
#include <HUDText.h>
#include <SpriteSet.h>
#include <RadiusData.h>

class Tmpl8::Surface;

class Renderer {
public:
	Renderer();
	~Renderer();

	void reset();

	void addCollider(const Collider& c);
	void addRenderData(RenderData rs);
	void addRadiusData(RadiusData rd);
	void addHUDText(HUDText t);
	
	void addSpriteSet(SpriteSet ss);
	void addMapRenderData(const MapRenderData& mrd);
	void addParallaxRenderData(const ParallaxRenderData& prd);

	void clearRenderDatas();
	void clearParallaxRenderData();
	void clearColliders();
	void clearRadiusData();
	void clearTexts();

	void clearSpriteSets();

	void render(Surface* screen, const ResourceManager& resourceManager, const vec2& cameraOffset);

	void setDarkOverlay(bool darkOverlay_);
private:
	static const int MAXRENDERSETS = 100; //REMBEMBER THAT THEY FINISH FAST
	static const int MAXRENDERLAYERS = 4;
	static const int MAXCOLLIDERS = 100;
	static const int MAXRADIUS = 100;
	static const int MAXTEXTS = 100;
	static const int MAXSPRITESETS = 100;
	
	RenderData renderDatas[MAXRENDERLAYERS][MAXRENDERSETS]; 
	const MapRenderData* mapRenderData;
	const ParallaxRenderData* parallaxRenderData;
	const Collider* colliders[MAXCOLLIDERS];
	RadiusData radiusDatas[MAXRADIUS]; 
	HUDText texts[MAXTEXTS];
	SpriteSet spriteSets[MAXSPRITESETS];
	
	int renderDataCount[MAXRENDERLAYERS];
	int collidersCount;
	int radiusCount;
	int textsCount;
	int spriteSetCount;

	bool darkOverlay;
	bool crtEffect;

	Printer printer;

	void drawTile(int tileSize, int tx, int ty, Surface* screen, Surface* tileset, int x, int y);

};