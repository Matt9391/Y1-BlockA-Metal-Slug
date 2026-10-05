#include "precomp.h"
#include "Map.h"
#include <lib/json.hpp>
#include <MapLayer.h>
#include <MapRenderData.h>
#include <Spawners/EnemySpawner.h>
#include <Spawners/PowSpawner.h>
#include <Spawners/PowerUpSpawner.h>
#include <iostream>


Map::Map() :
	tiles(0,0),
	tileSize(0),
	pos(0,0),
	mapRenderData{nullptr},
	layerCount(MLN_COUNTS),
	layerObjCount(MOLN_COUNTS)
	{
		loadDataFromJson("assets/gameMapV9.tmj");
		loadMapRenderData();
	}

const MapRenderData& Map::getMapRenderData() const {
	return *this->mapRenderData;
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

	delete mapRenderData;
	mapRenderData = nullptr;
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

const MapLayer& Map::getLayer(MapLayerNames layerName) const {
	return this->layers[layerName];
}

Spawner** Map::getSpawners(int layer) const {
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
	this->tiles = vec2(static_cast<float>(data.at("width").get<int>()), 
					   static_cast<float>(data.at("height").get<int>()));
	this->tileSize = data.at("tileheight").get<int>();
	//filling map layers
	for (int i = 0; i < static_cast<int>(MapLayerNames::MLN_COUNTS); i++) {
		//current layer
		nlohmann::json layer = data.at("layers").at(i);

		MapLayerNames layerName = static_cast<MapLayerNames>(i);
		
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
				vec2(static_cast<float>(layer.value("offsetx", 0)),
					 static_cast<float>(layer.value("offsety", 0))), //return 0 if there's no offset
				vec2(static_cast<float>(layer.at("width").get<int>()), 
					 static_cast<float>(layer.at("height").get<int>())),
				this->tileSize
			);
		}else {
			this->layers[i] = MapLayer(
				ResourceID::ID_MAP_TILESET, //map tileset
				layerName,
				layerData,
				data.at("tilesets").at(0).at("firstgid").get<int>(), //firstGid for map tileset
				vec2(static_cast<float>(layer.value("offsetx", 0)),
					 static_cast<float>(layer.value("offsety", 0))), //return 0 if there's no offset
				vec2(static_cast<float>(layer.at("width").get<int>()), 
					 static_cast<float>(layer.at("height").get<int>())),
				this->tileSize
			);
		}

		delete[] layerData;
	}

	for(int i = 0; i< MapObjectLayerNames::MOLN_COUNTS; i++){

		//current layer
		nlohmann::json layer = data.at("layers").at(static_cast<size_t>(MapLayerNames::MLN_COUNTS + i));

		MapObjectLayerNames layerName = static_cast<MapObjectLayerNames>(i);
		
		if (layerName == MapObjectLayerNames::MOLN_ENEMY_SPAWNER_LAYER) {
			nlohmann::json dataObjects = layer.at("objects");
			int nOfObjects = static_cast<int>(layer.at("objects").size());

			spawners[MapObjectLayerNames::MOLN_ENEMY_SPAWNER_LAYER] = new Spawner*[nOfObjects];
			spawnerCounts[MapObjectLayerNames::MOLN_ENEMY_SPAWNER_LAYER] = nOfObjects;

			for (int j = 0; j < nOfObjects; j++) {
				nlohmann::json spawner = dataObjects[j];
				nlohmann::json properties = spawner.at("properties");

				int enemyType = properties[0].at("value").get<int>();
				int nOfEnemy = properties[1].at("value").get<int>();
				float spawnDelay = static_cast<float>(properties[2].at("value").get<int>());
				vec2 spPos = vec2(static_cast<float>(spawner.at("x").get<int>()), static_cast<float>(spawner.at("y").get<int>()));
				vec2 size = vec2(static_cast<float>(spawner.at("width").get<int>()), static_cast<float>(spawner.at("height").get<int>()));
				
				spawners[MapObjectLayerNames::MOLN_ENEMY_SPAWNER_LAYER][j] = new EnemySpawner(spPos, size, spawnDelay, enemyType, nOfEnemy);
			}


			continue;
		}else if (layerName == MapObjectLayerNames::MOLN_POW_SPAWNER_LAYER) {
			nlohmann::json dataObjects = layer.at("objects");
			int nOfObjects = static_cast<int>(layer.at("objects").size());

			spawners[MapObjectLayerNames::MOLN_POW_SPAWNER_LAYER] = new Spawner *[nOfObjects];
			spawnerCounts[MapObjectLayerNames::MOLN_POW_SPAWNER_LAYER] = nOfObjects;

			for (int j = 0; j < nOfObjects; j++) {
				nlohmann::json spawner = dataObjects[j];
				nlohmann::json properties = spawner.at("properties");

				int enemyType = properties[0].at("value").get<int>();
				vec2 spPos = vec2(static_cast<float>(spawner.at("x").get<int>()), static_cast<float>(spawner.at("y").get<int>()));
				vec2 size = vec2(static_cast<float>(spawner.at("width").get<int>()), static_cast<float>(spawner.at("height").get<int>()));

				spawners[MapObjectLayerNames::MOLN_POW_SPAWNER_LAYER][j] = new PowSpawner(spPos, size, 0, enemyType);
			}


			continue;
		}else if (layerName == MapObjectLayerNames::MOLN_POWERUP_SPAWNER_LAYER) {
			nlohmann::json dataObjects = layer.at("objects");
			int nOfObjects = static_cast<int>(layer.at("objects").size());

			spawners[MapObjectLayerNames::MOLN_POWERUP_SPAWNER_LAYER] = new Spawner *[nOfObjects];
			spawnerCounts[MapObjectLayerNames::MOLN_POWERUP_SPAWNER_LAYER] = nOfObjects;

			for (int j = 0; j < nOfObjects; j++) {
				nlohmann::json spawner = dataObjects[j];
				nlohmann::json properties = spawner.at("properties");

				int state = properties[0].at("value").get<int>();
				vec2 spPos = vec2(static_cast<float>(spawner.at("x").get<int>()), static_cast<float>(spawner.at("y").get<int>()));
				vec2 size = vec2(static_cast<float>(spawner.at("width").get<int>()), static_cast<float>(spawner.at("height").get<int>()));

				spawners[MapObjectLayerNames::MOLN_POWERUP_SPAWNER_LAYER][j] = new PowerUpSpawner(spPos, size, 0, state);
			}


			continue;
		}

	}

	return true;
}



void Map::loadMapRenderData() {
	//MapRenderData(this->spPos, this->tileSize, this->layers, this->spawners);
	mapRenderData = new MapRenderData(
		this->pos,
		this->tileSize, 
		layerCount,
		layerObjCount,
		this->layers, 
		this->spawners,
		this->spawnerCounts
	);
}