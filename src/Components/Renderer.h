#pragma once

#include <RenderContainer.h>
#include <MapRenderContainer.h>
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
	void addRenderContainer(RenderContainer rs);
	void addHUDText(HUDText t);
	
	void addSpriteSet(SpriteSet ss);
	void addMapRenderContainer(const MapRenderContainer& mrs);

	void clearRenderContainers();
	void clearColliders();
	void clearTexts();

	void clearSpriteSets();

	void render(Surface* screen, const ResourceManager& resourceManager, const vec2& cameraOffset);

private:
	static const int MAXRENDERSETS = 100; //REMBEMBER THAT THEY FINISH FAST
	static const int MAXCOLLIDERS = 100;
	static const int MAXTEXTS = 100;
	static const int MAXSPRITESETS = 100;
	
	RenderContainer renderContainers[MAXRENDERSETS]; //dont describe it meaning
	const MapRenderContainer* mapRenderContainer;
	const Collider* colliders[MAXCOLLIDERS];
	HUDText texts[MAXTEXTS];
	SpriteSet spriteSets[MAXSPRITESETS];
	
	int renderContainerCount;
	int collidersCount;
	int textsCount;
	int spriteSetCount;


	Printer printer;
};