#pragma once

#include <vec2.h>
#include <MapLayerNames.h>
#include <MapLayer.h>


struct MapRenderSet {
	vec2 pos;
	int tileSize;

	int layerCount;
	int layerObjCount;
	MapLayer layers[MapLayerNames::MLN_COUNTS];
	MapObjLayer objectLayers[MapObjectLayerNames::MOLN_COUNTS];
	MapRenderSet() :
		pos(vec2(0,0)),
		tileSize(0),
		layerCount(MapLayerNames::MLN_COUNTS),
		layerObjCount(MapObjectLayerNames::MOLN_COUNTS)
	{
		for (int i = 0; i < MapLayerNames::MLN_COUNTS; i++) {
			this->layers[i] = MapLayer();
		}
		for (int i = 0; i < MapObjectLayerNames::MOLN_COUNTS; i++) {
			this->objectLayers[i] = MapObjLayer();
		}
	}
	
	MapRenderSet(const vec2 pos, const int tileSize, const MapLayer* layers, const MapObjLayer* objectLayers) :
		pos(pos),
		tileSize(tileSize),
		layerCount(MapLayerNames::MLN_COUNTS),
		layerObjCount(MapObjectLayerNames::MOLN_COUNTS)
	{
		for (int i = 0; i < MapLayerNames::MLN_COUNTS; i++) {
			this->layers[i] = layers[i];
		}

		for (int i = 0; i < MapObjectLayerNames::MOLN_COUNTS; i++) {
			this->objectLayers[i] = objectLayers[i];
		}
	}
};