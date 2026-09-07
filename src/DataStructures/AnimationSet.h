#pragma once
#include <AnimationLayer.h>


struct AnimationSet {
	static const int MAX_LAYERS = 2;

	AnimationLayer layers[MAX_LAYERS];
	int layerCount;

	AnimationSet(int layerCount, AnimationLayer firstLayer, AnimationLayer secondLayer = AnimationLayer()) {
		this->layerCount = layerCount;
		layers[0] = firstLayer;
		layers[1] = secondLayer;
	}

	AnimationSet() {
		this->layerCount = -1;
		layers[0] = AnimationLayer();
		layers[1] = AnimationLayer();
	}

};