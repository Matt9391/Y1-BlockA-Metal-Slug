#pragma once

#include <vec2.h>
#include <ResourceID.h>

class MapLayer {
	
	MapLayer() {
		this->resourceId = ResourceID::ID_NULL;
		this->layerName = nullptr;
		this->data = nullptr;
		this->firstgid = -1;
		this->offset = vec2(0, 0);
	}

	~MapLayer() {
		delete[] data;
	}


	void setMapLayer(ResourceID resourceId, char* layerName, int* data, int firstgid, vec2 offset) {
		this->resourceId = resourceId;
		this->layerName = layerName;
		this->data = data;
		this->firstgid = firstgid;
		this->offset = offset;
	}


private:
	ResourceID resourceId;
	vec2 offset;
	char* layerName;
	int* data;
	int firstgid;
};