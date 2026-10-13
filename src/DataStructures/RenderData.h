#pragma once

#include <AnimationSet.h>
#include <vec2.h>

struct RenderData {

	RenderData() {
		animationSet = AnimationSet();
		pos = vec2(0, 0);
		layer = 1;
	}

	RenderData(AnimationSet animationSet, vec2 pos, int layer = 1) {
		this->animationSet = animationSet;
		this->pos = pos;
		this->layer = layer;
	}

	AnimationSet animationSet;
	vec2 pos;
	int layer;
};