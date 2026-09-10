#pragma once

#include <RenderSet.h>
#include <MapRenderSet.h>
#include <ResourceManager.h>

class Tmpl8::Surface;

class Renderer {
public:
	Renderer();

	void addRenderSet(RenderSet rs);
	void addMapRenderSet(const MapRenderSet& mrs);

	void clearRenderSets();

	void render(Surface* screen, const ResourceManager& resourceManager);

private:
	static const int MAXRENDERSETS = 10;
	RenderSet renderSets[MAXRENDERSETS];
	MapRenderSet mapRenderSet;
	int renderSetCount;
};