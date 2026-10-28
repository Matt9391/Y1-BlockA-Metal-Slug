// Map - the level loaded from the Tiled file: the tile layers (graphics + collision) and the spawners from
// the object layers. It is loaded once by the ResourceManager and shared by every GameScene.
#pragma once

#include <vec2.h>
#include <MapLayer.h>
#include <MapLayerNames.h>
#include <Spawner.h>
#include <MapRenderData.h>

class Map
{
public:
	Map();
	~Map();
	const MapRenderData& getMapRenderData() const; // references to the map data, for the Renderer
	vec2 getTiles() const; // map size in tiles
	int getTileSize() const;
	Spawner** getSpawners(int layer) const; // array of spawners of object layer 'layer'
	const int* getSpawnersCount() const; // how many spawners each object layer has
	const int& getSpawnersLayers() const; // number of object layers

	MapLayer& getLayer(MapLayerNames layerName) ;
	const MapLayer& getLayer(MapLayerNames layerName) const;

private:
	bool loadDataFromJson(const char* fileName); // parse the .tmj file
	void loadMapRenderData(); // build mapRenderData (references to the members below)

	vec2 pos; // world position of the map (always 0,0)
	vec2 tiles;
	int tileSize;

	MapLayer layers[MapLayerNames::MLN_COUNTS];
	Spawner** spawners[MapObjectLayerNames::MOLN_COUNTS]; // per object layer, a heap array of Spawner* (Spawner is abstract, hence pointers)
	int spawnerCounts[MapObjectLayerNames::MOLN_COUNTS];
	int layerCount;
	int layerObjCount;
	MapRenderData* mapRenderData;
};

