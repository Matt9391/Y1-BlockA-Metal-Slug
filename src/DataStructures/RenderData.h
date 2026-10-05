#pragma once

#include <AnimationSet.h>
#include <vec2.h>

struct RenderData {

	RenderData() {
		animationSet = AnimationSet();
		pos = vec2(0, 0);
	}

	RenderData(AnimationSet animationSet, vec2 pos) {
		this->animationSet = animationSet;
		this->pos = pos;
	}

	AnimationSet animationSet;
	vec2 pos;
};