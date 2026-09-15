#pragma once

#include <RenderSet.h>
#include <MapRenderSet.h>
#include <ResourceManager.h>
#include <Collider.h>

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
	static const int MAXRENDERSETS = 10;
	static const int MAXCOLLIDERS = 10;
	RenderSet renderSets[MAXRENDERSETS];
	MapRenderSet mapRenderSet;
	Collider* colliders[MAXCOLLIDERS];
	int renderSetCount;
	int collidersCount;
};