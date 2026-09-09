#include "precomp.h"
#include "Map.h"
#include <lib/json.hpp>

Map::Map() :
	tiles(0,0),
	tileSize(0)
	{
		loadDataFromJson("assets/gameMap.tmj");
	}

bool Map::loadDataFromJson(const char* fileName) {

	//File reading
	std::ifstream map(fileName);
	nlohmann::json data = nlohmann::json::parse(map);


	//filling member variables
	this->tiles = vec2(data.at("width").get<int>(), data.at("height").get<int>());
	this->tileSize = data.at("tileheight");

	//filling map layers
	for (int i = 0; i < static_cast<int>(MapLayerNames::MLN_COUNTS); i++) {
		//current layer
		nlohmann::json layer = data.at("layers").at(i);
		//data (tiles) of current layer
		nlohmann::json mapData = layer.at("data");

		std::string layerName = layer.at("name").get<std::string>();

		//size of the array of tiles
		int dataSize = static_cast<int>(mapData.size());

		int* layerData = new int[dataSize];

		for (int j = 0; j < dataSize; j++) {
			layerData[j] = mapData.at(j).get<int>();
		}

		//the third layer is always the collison layer, design choice
		if (i == MLN_COLLISION_LAYER) {
			this->layers[i].setMapLayer(
				ResourceID::ID_COLLISION_TILESET, //collision tileset
				layerName.c_str(),
				layerData,
				data.at("tilesets").at(1).at("firstgid").get<int>(), //firstGid for collision tileset
				vec2(layer.value("offsetx", 0), layer.value("offsety", 0)), //return 0 if there's no offset
				vec2(layer.at("width").get<int>(), layer.at("height").get<int>())
			);
		}
		else {
			this->layers[i].setMapLayer(
				ResourceID::ID_MAP_TILESET, //map tileset
				layerName.c_str(),
				layerData,
				data.at("tilesets").at(0).at("firstgid").get<int>(), //firstGid for map tileset
				vec2(layer.value("offsetx", 0), layer.value("offsety", 0)), //return 0 if there's no offset
				vec2(layer.at("width").get<int>(), layer.at("height").get<int>())
			);
		}

		delete[] layerData;
	}

	return true;
}

