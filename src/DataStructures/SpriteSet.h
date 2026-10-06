#pragma once

#include <vec2.h>

enum ResourceID : int;
enum ResourceIDFrames : int;

struct SpriteSet {
	ResourceID resourceId;
	ResourceIDFrames frames;
	int currentFrame;
	vec2 pos;

	SpriteSet(
		ResourceID resourceId = static_cast<ResourceID>(-1),
		ResourceIDFrames frames = static_cast<ResourceIDFrames>(-1),
		vec2 pos = vec2(0, 0),
		int currentFrame = 0
	)
		: resourceId(resourceId),
		frames(frames),
		pos(pos),
		currentFrame(currentFrame)
	{
	}
};