#include "precomp.h"
#include "MapLayer.h"
#include <MapLayerNames.h>

MapLayer::MapLayer() {
	this->resourceId = ResourceID::ID_NULL;
	this->layerName = MapLayerNames::MLN_NULL_LAYER;
	this->data = nullptr;
	this->firstgid = -1;
	this->offset = vec2(0, 0);
	this->tiles = vec2(0, 0);
}

MapLayer::~MapLayer() {
	delete[] data;
}

MapLayer::MapLayer(const ResourceID resourceId, MapLayerNames layerName, const int* data, const int firstgid, const vec2& offset, const vec2& tiles) :
data(nullptr)
{
	this->resourceId = resourceId;
	this->firstgid = firstgid;
	this->offset = offset;
	this->tiles = tiles;	
	this->layerName = layerName;

	
	//delete current data array if allocated before allocate it again
	delete[] this->data;

	int dataSize = tiles.x * tiles.y;

	this->data = new int[dataSize];

	for(int i = 0; i < dataSize; i++){
		this->data[i] = data[i];
	}
}

void MapLayer::operator=(const MapLayer& other) {
	this->resourceId = other.resourceId;
	this->firstgid = other.firstgid;
	this->offset = other.offset;
	this->tiles = other.tiles;
	this->layerName = other.layerName;

	delete[] this->data;

	int dataSize = tiles.x * tiles.y;

	this->data = new int[dataSize];

	for (int i = 0; i < dataSize; i++) {
		this->data[i] = other.data[i];
	}
}