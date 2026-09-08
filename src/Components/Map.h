#pragma once

#include <vec2.h>
#include <MapLayer.h>
#include <MapLayerNames.h>

class Map
{
public:
	Map();

	bool defineDataFromJson(const char* fileName);
	bool loadDataFromJson(const char* fileName);

private:

	vec2 tiles;
	int tileSize;

	MapLayer layers[MapLayerNames::MLN_COUNTS];

};

