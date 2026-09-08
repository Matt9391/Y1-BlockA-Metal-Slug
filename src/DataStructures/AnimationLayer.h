#pragma once
#include <vec2.h>
#include <ResourceID.h>

class Tmpl8::Sprite;

struct AnimationLayer {
	ResourceID resourceId;
	Sprite* sprite;

	int nFrames;
	int currentFrame;

	float frameDuration;
	vec2 offset;

	AnimationLayer(Sprite* sprite, ResourceID resourceId, float frameDuration, vec2 offset = vec2(0, 0)) {
		this->sprite = sprite;
		this->nFrames = sprite->Frames();
		this->frameDuration = frameDuration;
		this->currentFrame = 0;
		this->offset = offset;
		this->resourceId = resourceId;
	}

	AnimationLayer() {
		this->sprite = nullptr;
		this->nFrames = -1;
		this->frameDuration = -1;
		this->currentFrame = -1;
		this->offset = vec2(0,0);
		this->resourceId = ResourceID::ID_NULL;
	}

	//I built my own operator because in "Animator.cpp" I check if an animation is the same as another but I thought that the animation layer should do the check, not the animator class
	bool operator==(const AnimationLayer& other) const {
		return this->resourceId == other.resourceId
			&& this->offset == other.offset
			&& this->frameDuration == other.frameDuration;
	}
	
	bool operator!=(const AnimationLayer& other) const {
		return !(*this == other);
	}
};