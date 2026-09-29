#include "precomp.h"
#include "Map.h"
#include <lib/json.hpp>
#include <MapLayer.h>
#include <MapRenderSet.h>
#include <Spawners/EnemySpawner.h>
#include <iostream>


Map::Map() :
	tiles(0,0),
	tileSize(0),
	pos(0,0),
	mapRenderSet{nullptr},
	layerCount(MLN_COUNTS),
	layerObjCount(MOLN_COUNTS)
	{
		loadDataFromJson("assets/gameMapV7.tmj");
		loadMapRenderSet();
		printf("\nOBJECT LAYER COUNT PRE: %d", mapRenderSet->layerObjCount);
	}

const MapRenderSet& Map::getMapRenderSet() const {
	return *this->mapRenderSet;
}

Map::~Map()
{
	//delete every spawner in every spawner layer
	for (int i = 0; i < MapObjectLayerNames::MOLN_COUNTS; i++)
	{
		if (spawners[i] != nullptr)
		{
			for (int j = 0; j < spawnerCounts[i]; j++)
			{
				delete spawners[i][j];
			}

			delete[] spawners[i];
			spawners[i] = nullptr;
		}

		spawnerCounts[i] = 0;
	}

	delete mapRenderSet;
	mapRenderSet = nullptr;
}

vec2 Map::getTiles() const {
	return this->tiles;
}

int Map::getTileSize() const {
	return this->tileSize;
}

MapLayer& Map::getLayer(MapLayerNames layerName) {
	return this->layers[layerName];
}

Spawner** Map::getSpawners(int layer) {
	return spawners[layer];
}

const int* Map::getSpawnersCount() const {
	return this->spawnerCounts;
}

const int& Map::getSpawnersLayers() const {
	return this->layerObjCount;
}

bool Map::loadDataFromJson(const char* fileName) {

	//File reading
	std::ifstream map(fileName);
	nlohmann::json data = nlohmann::json::parse(map);


	//filling member variables
	this->tiles = vec2(data.at("width").get<int>(), data.at("height").get<int>());
	this->tileSize = data.at("tileheight").get<int>();
	//filling map layers
	for (int i = 0; i < static_cast<int>(MapLayerNames::MLN_COUNTS); i++) {
		//current layer
		nlohmann::json layer = data.at("layers").at(i);

		MapLayerNames layerName = static_cast<MapLayerNames>(i);
		
		if (layerName == MapLayerNames::MLN_ENEMY_SPAWNER_LAYER) {
			nlohmann::json dataObjects = layer.at("objects");
			int nOfObjects = layer.at("objects").size();
			std::cout << nOfObjects << std::endl;

			spawners[MapObjectLayerNames::MOLN_ENEMY_SPAWNER_LAYER] = new Spawner*[nOfObjects];
			spawnerCounts[MapObjectLayerNames::MOLN_ENEMY_SPAWNER_LAYER] = nOfObjects;

			for (int i = 0; i < nOfObjects; i++) {
				nlohmann::json eSpawner = dataObjects[i];
				nlohmann::json properties = eSpawner.at("properties");

				int enemyType = properties[0].at("value").get<int>();
				int nOfEnemy = properties[1].at("value").get<int>();
				float spawnDelay = properties[2].at("value").get<int>();
				vec2 pos = vec2(eSpawner.at("x").get<int>(), eSpawner.at("y").get<int>());
				vec2 size = vec2(eSpawner.at("width").get<int>(), eSpawner.at("height").get<int>());
				
				spawners[MapObjectLayerNames::MOLN_ENEMY_SPAWNER_LAYER][i] = new EnemySpawner(pos, size, spawnDelay, enemyType, nOfEnemy);
			}


			continue;
		}

		//data (tiles) of current layer
		nlohmann::json mapData = layer.at("data");


		//size of the array of tiles
		int dataSize = static_cast<int>(mapData.size());

		int* layerData = new int[dataSize];

		for (int j = 0; j < dataSize; j++) {
			layerData[j] = mapData.at(j).get<int>();
		}

		//the third layer is always the collison layer, design choice
		if (i == MLN_COLLISION_LAYER) {
			this->layers[i] = MapLayer(
				ResourceID::ID_COLLISION_TILESET, //collision tileset
				layerName,
				layerData,
				data.at("tilesets").at(1).at("firstgid").get<int>(), //firstGid for collision tileset
				vec2(layer.value("offsetx", 0), layer.value("offsety", 0)), //return 0 if there's no offset
				vec2(layer.at("width").get<int>(), layer.at("height").get<int>()),
				this->tileSize
			);
		}else {
			this->layers[i] = MapLayer(
				ResourceID::ID_MAP_TILESET, //map tileset
				layerName,
				layerData,
				data.at("tilesets").at(0).at("firstgid").get<int>(), //firstGid for map tileset
				vec2(layer.value("offsetx", 0), layer.value("offsety", 0)), //return 0 if there's no offset
				vec2(layer.at("width").get<int>(), layer.at("height").get<int>()),
				this->tileSize
			);
		}

		delete[] layerData;
	}

	return true;
}


void Map::loadMapRenderSet() {
	//MapRenderSet(this->pos, this->tileSize, this->layers, this->spawners);
	mapRenderSet = new MapRenderSet(
		this->pos,
		this->tileSize, 
		layerCount,
		layerObjCount,
		this->layers, 
		this->spawners,
		this->spawnerCounts
	);
}