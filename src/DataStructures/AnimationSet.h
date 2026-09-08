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


	//I built my own operator because in "Animator.cpp" I check if an animation is the same as another but I thought that the animation set should do the check its layer, not the animator class
	bool operator==(const AnimationSet& other) const {
		if (this->layerCount != other.layerCount) return false;

		bool same = true;

		for (int i = 0; i < this->layerCount; i++) {
			if (this->layers[i] != other.layers[i]) {
				same = false;
				break;
			}
		}

		return same;

		
	}

};