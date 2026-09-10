#pragma once

#include <vec2.h>
#include <MapLayer.h>
#include <MapLayerNames.h>
#include <MapRenderSet.h>

class Map
{
public:
	Map();
	bool loadDataFromJson(const char* fileName);

	MapRenderSet getMapRenderSet();
	vec2 getTiles() const;
	int getTileSize() const;

private:
	vec2 pos;
	vec2 tiles;
	int tileSize;

	MapLayer layers[MapLayerNames::MLN_COUNTS];

};

