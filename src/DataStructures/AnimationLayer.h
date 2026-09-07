#pragma once

class Tmpl8::Sprite;

struct AnimationLayer {
	Sprite* sprite;

	int nFrames;
	int currentFrame;

	float frameDuration;
	
	AnimationLayer(Sprite* sprite, int nFrames, float frameDuration) {
		this->sprite = sprite;
		this->nFrames = nFrames;
		this->frameDuration = frameDuration;
		this->currentFrame = 0;
	}

	AnimationLayer() {
		this->sprite = nullptr;
		this->nFrames = -1;
		this->frameDuration = -1;
		this->currentFrame = -1;
	}
};