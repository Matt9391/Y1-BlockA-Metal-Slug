#pragma once
#include <vec2.h>

class Tmpl8::Sprite;

struct AnimationLayer {
	Sprite* sprite;

	int nFrames;
	int currentFrame;

	float frameDuration;
	vec2 offset;

	AnimationLayer(Sprite* sprite, int nFrames, float frameDuration, vec2 offset = vec2(0,0)) {
		this->sprite = sprite;
		this->nFrames = nFrames;
		this->frameDuration = frameDuration;
		this->currentFrame = 0;
		this->offset = offset;
	}

	AnimationLayer() {
		this->sprite = nullptr;
		this->nFrames = -1;
		this->frameDuration = -1;
		this->currentFrame = -1;
		this->offset = vec2(0,0);
	}
};