#pragma once

#include <vec2.h>
#include <MapLayerNames.h>
#include <MapLayer.h>


struct MapRenderSet {
	vec2 pos;
	int tileSize;

	int layerCount;
	MapLayer layers[MapLayerNames::MLN_COUNTS];

	MapRenderSet() {
		this->pos = vec2(0, 0);
		this->tileSize = 0;
		this->layerCount = MapLayerNames::MLN_COUNTS;
		for (int i = 0; i < MapLayerNames::MLN_COUNTS; i++) {
			this->layers[i] = MapLayer();
		}
	}
	
	MapRenderSet(const vec2 pos, const int tileSize, const MapLayer* layers) {
		this->pos = pos;
		this->tileSize = tileSize;
		this->layerCount = MapLayerNames::MLN_COUNTS;
		for (int i = 0; i < MapLayerNames::MLN_COUNTS; i++) {
			this->layers[i] = layers[i];
		}
	}
};