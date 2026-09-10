#pragma once

#include <vec2.h>
#include <MapLayerNames.h>
#include <MapLayer.h>


struct MapRenderSet {
	vec2 pos;
	int tileSize;

	int layerCount;
	MapLayer layers[MapLayerNames::MLN_COUNTS];

	MapRenderSet() :
		pos(vec2(0,0)),
		tileSize(0),
		layerCount(MapLayerNames::MLN_COUNTS)
	{
		for (int i = 0; i < MapLayerNames::MLN_COUNTS; i++) {
			this->layers[i] = MapLayer();
		}
	}
	
	MapRenderSet(const vec2 pos, const int tileSize, const MapLayer* layers) :
		pos(pos),
		tileSize(tileSize),
		layerCount(MapLayerNames::MLN_COUNTS)
	{
		for (int i = 0; i < MapLayerNames::MLN_COUNTS; i++) {
			this->layers[i] = layers[i];
		}
	}
};