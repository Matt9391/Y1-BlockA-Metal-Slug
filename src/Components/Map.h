#pragma once

#include <vec2.h>
#include <MapLayer.h>
#include <MapLayerNames.h>
#include <Spawner.h>
#include <MapRenderSet.h>

class Map
{
public:
	Map();
	const MapRenderSet& getMapRenderSet() const;
	vec2 getTiles() const;
	int getTileSize() const;

	MapLayer& getLayer(MapLayerNames layerName);

private:
	bool loadDataFromJson(const char* fileName);
	void loadMapRenderSet();

	vec2 pos;
	vec2 tiles;
	int tileSize;

	MapLayer layers[MapLayerNames::MLN_COUNTS];
	Spawner** spawners[MapObjectLayerNames::MOLN_COUNTS];
	int spawnerCounts[MapObjectLayerNames::MOLN_COUNTS];
	int layerCount;
	int layerObjCount;
	MapRenderSet* mapRenderSet;
};

