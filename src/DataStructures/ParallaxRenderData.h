#pragma once

#include <vec2.h>

enum ResourceID : int;
enum ResourceIDFrames : int;

struct ParallaxRenderData {
	ResourceID resourceId;
	ResourceIDFrames frames;
	float parallaxFactor;
	vec2 pos;
	int currentFrame;

	ParallaxRenderData(
		ResourceID resourceId = static_cast<ResourceID>(-1),
		ResourceIDFrames frames = static_cast<ResourceIDFrames>(-1),
		float parallaxFactor = 1.f,
		vec2 pos = vec2(0, 0),
		int currentFrame = 0
	)
		: 
		resourceId(resourceId),
		frames(frames),
		parallaxFactor(parallaxFactor),
		pos(pos),
		currentFrame(currentFrame)
	{
	}
};