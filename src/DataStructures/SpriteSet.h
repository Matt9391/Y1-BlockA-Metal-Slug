#pragma once

#include "vec2.h"

enum ResourceID;
enum ResourceIDFrames;

struct SpriteSet {
	ResourceID resourceId;
	ResourceIDFrames frames;
	vec2 pos;

	SpriteSet(
		ResourceID resourceId = static_cast<ResourceID>(-1),
		ResourceIDFrames frames = static_cast<ResourceIDFrames>(-1),
		vec2 pos = vec2(0, 0)
	)
		: resourceId(resourceId),
		frames(frames),
		pos(pos)
	{
	}
};