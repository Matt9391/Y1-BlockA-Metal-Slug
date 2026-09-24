#pragma once

#include <RenderSet.h>
#include <MapRenderSet.h>
#include <ResourceManager.h>
#include <Collider.h>
#include <Printer.h>

class Tmpl8::Surface;

class Renderer {
public:
	Renderer();

	void addCollider(Collider& c);
	void addRenderSet(RenderSet rs);
	
	void addMapRenderSet(const MapRenderSet& mrs);

	void clearRenderSets();
	void clearColliders();

	void render(Surface* screen, const ResourceManager& resourceManager, const vec2& cameraOffset);

private:
	static const int MAXRENDERSETS = 100; //REMBEMBER THAT THEY FINISH FAST
	static const int MAXCOLLIDERS = 100;
	RenderSet renderSets[MAXRENDERSETS];
	MapRenderSet mapRenderSet;
	Collider* colliders[MAXCOLLIDERS];
	int renderSetCount;
	int collidersCount;

	Printer printer;
};