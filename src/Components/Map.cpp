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
	std::ifstream map(fileName);
	nlohmann::json data = nlohmann::json::parse(map);

	this->tiles = vec2(data.at("width").get<int>(), data.at("height").get<int>());
	this->tileSize = data.at("tileheight");

	for (int i = 0; i < static_cast<int>(MapLayerNames::MLN_COUNTS); i++) {
		nlohmann::json layer = data.at("layers").at(i);
		nlohmann::json mapData = data.at("layers").at(i).at("data");

		std::string name = layer.at("name").get<std::string>();

		int dataSize = static_cast<int>(mapData.size());

		int* layerData = new int[dataSize];

		for (int j = 0; j < dataSize; j++) {
			layerData[j] = mapData.at(j).get<int>();
		}

		//the third layer is always the collison layer, design choice
		if (i == 3) {
	
			this->layers[i].setMapLayer(
				ResourceID::ID_COLLISION_TILESET,
				name.c_str(),
				layerData,
				data.at("tilesets").at(1).at("firstgid").get<int>(),
				vec2(layer.value("offsetx", 0), layer.value("offsety", 0)),
				vec2(layer.at("width").get<int>(), layer.at("height").get<int>())
			);
		}
		else {
			this->layers[i].setMapLayer(
				ResourceID::ID_MAP_TILESET,
				name.c_str(),
				layerData,
				data.at("tilesets").at(0).at("firstgid").get<int>(),
				vec2(layer.value("offsetx", 0), layer.value("offsety", 0)),
				vec2(layer.at("width").get<int>(), layer.at("height").get<int>())
			);
		}

		delete[] layerData;
	}

	return true;
}

