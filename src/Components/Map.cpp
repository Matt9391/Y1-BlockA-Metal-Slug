#include "precomp.h"
#include "Map.h"
#include <lib/json.hpp>

Map::Map() :
	tiles(0,0),
	tileSize(0)
	{
		
	}

bool Map::defineDataFromJson(const char* fileName) {
	std::ifstream map(fileName);
	nlohmann::json data = nlohmann::json::parse(map);
	
	int dataSize = data.at("width").get<int>() * data.at("height").get<int>();

	for (int i = 0; i < static_cast<int>(MapLayerNames::MLN_COUNTS); i++) {
		//this->layers[i].data = new int[dataSize];
	}

}

