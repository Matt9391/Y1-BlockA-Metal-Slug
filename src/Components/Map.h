#pragma once

#include <vec2.h>
#include <MapLayer.h>
#include <MapLayerNames.h>

struct MapRenderSet;
struct MapObjectRenderSet;

class Map
{
public:
	Map();

	MapRenderSet getMapRenderSet() const;
	vec2 getTiles() const;
	int getTileSize() const;

	MapLayer& getLayer(MapLayerNames layerName);

private:
	bool loadDataFromJson(const char* fileName);

	vec2 pos;
	vec2 tiles;
	int tileSize;

	MapLayer layers[MapLayerNames::MLN_COUNTS];
	MapObjLayer objLayers[MapObjectLayerNames::MOLN_COUNTS];

};

