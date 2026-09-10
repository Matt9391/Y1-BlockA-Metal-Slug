#pragma once

#include <vec2.h>
#include <ResourceID.h>
#include <MapLayerNames.h>

struct MapLayer {
public:

	MapLayer();
	~MapLayer();

	MapLayer(const ResourceID resourceId, MapLayerNames layerName, const int* data,const int firstgid,const vec2& offset, const vec2& tiles);

	void operator=(const MapLayer& other);

	ResourceID resourceId;
	vec2 offset;
	vec2 tiles;
	MapLayerNames layerName;
	int* data;
	int firstgid;
};