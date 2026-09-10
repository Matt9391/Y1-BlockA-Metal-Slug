#pragma once
#include <vec2.h>
#include <ResourceID.h>

class Tmpl8::Sprite;

struct AnimationLayer {
	ResourceID resourceId;

	int nFrames;
	int currentFrame;

	float frameDuration;
	vec2 offset;

	AnimationLayer(ResourceID resourceId, int nFrames, float frameDuration, vec2 offset = vec2(0, 0)) :
		nFrames(nFrames),
		frameDuration(frameDuration),
		currentFrame(0),
		offset(offset),
		resourceId(resourceId)	
	{}

	AnimationLayer() :
		nFrames(-1),
		frameDuration(-1),
		currentFrame(0),
		offset(0,0),
		resourceId(ResourceID::ID_NULL)
	{}

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