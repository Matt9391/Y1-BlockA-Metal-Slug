#pragma once

#include <vec2.h>
#include <ResourceID.h>
#include <MapLayerNames.h>

struct MapLayer {
public:

	ResourceID resourceId;
	vec2 offset;
	vec2 tiles;
	MapLayerNames layerName;
	int* data;
	int firstgid;

	MapLayer() :
		resourceId(ResourceID::ID_NULL),
		layerName(MapLayerNames::MLN_NULL_LAYER),
		data(nullptr),
		firstgid(-1),
		offset(0,0),
		tiles(0,0) 
	{}
	~MapLayer() {
		delete[] data;
	}

	MapLayer(const ResourceID resourceId, MapLayerNames layerName, const int* data,const int firstgid,const vec2& offset, const vec2& tiles) :
		resourceId(resourceId),
		layerName(layerName),
		data(nullptr),
		firstgid(firstgid),
		offset(offset),
		tiles(tiles)
	{
		//delete current data array if allocated before allocate it again
		delete[] this->data;

		int dataSize = tiles.x * tiles.y;

		this->data = new int[dataSize];

		for (int i = 0; i < dataSize; i++) {
			this->data[i] = data[i];
		}
	}

	void operator=(const MapLayer& other) {
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

};