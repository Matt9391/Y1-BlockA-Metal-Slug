#pragma once

#include <vec2.h>
#include <ResourceID.h>

class MapLayer {
public:

	MapLayer();
	~MapLayer();

	void setMapLayer(const ResourceID resourceId, const char* layerName, const int* data,const int firstgid,const vec2& offset, const vec2& tiles);


private:
	ResourceID resourceId;
	vec2 offset;
	vec2 tiles;
	char* layerName;
	int* data;
	int firstgid;
};