#pragma once

#include <vec2.h>
#include <MapLayer.h>
#include <MapLayerNames.h>
#include <MapRenderSet.h>

class Map
{
public:
	Map();

	MapRenderSet getMapRenderSet() const;
	vec2 getTiles() const;
	int getTileSize() const;

private:
	bool loadDataFromJson(const char* fileName);


	vec2 pos;
	vec2 tiles;
	int tileSize;

	MapLayer layers[MapLayerNames::MLN_COUNTS];

};

