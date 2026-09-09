#include "precomp.h"
#include "MapLayer.h"

MapLayer::MapLayer() {
	this->resourceId = ResourceID::ID_NULL;
	this->layerName = nullptr;
	this->data = nullptr;
	this->firstgid = -1;
	this->offset = vec2(0, 0);
	this->tiles = vec2(0, 0);
}

MapLayer::~MapLayer() {
	delete[] data;
	delete[] this->layerName;
}

void MapLayer::setMapLayer(const ResourceID resourceId, const char* layerName, const int* data, const int firstgid, const vec2& offset, const vec2& tiles) {
	this->resourceId = resourceId;
	this->firstgid = firstgid;
	this->offset = offset;
	this->tiles = tiles;	

	delete[] this->layerName;
	this->layerName = new char[strlen(layerName) + 1];
	strcpy(this->layerName, layerName);

	delete[] this->data;

	int dataSize = tiles.x * tiles.y;

	this->data = new int[dataSize];

	for(int i = 0; i < dataSize; i++){
		this->data[i] = data[i];
	}
}
