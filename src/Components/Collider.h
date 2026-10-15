#pragma once

#include <vec2.h>
#include <ResourceID.h>

struct Collider {

	Collider() :
		pos(vec2(0,0)),
		size(vec2(0,0)),
		offset(vec2(0,0)),
		overlap(false),
		id{ResourceID::ID_NULL},
		frame{0},
		spriteOffset{vec2(0,0)},
		layerCount(0),
		flipped(false)
	{}

	Collider(const vec2& pos, vec2 size, vec2 offset) :
		pos(pos),
		size(size),
		offset(offset),
		overlap(false),
		id{ResourceID::ID_NULL},
		frame{0},
		spriteOffset{vec2(0,0)},
		layerCount(0),
		flipped(false)
	{ }

	vec2 offset;
	const vec2& pos;
	vec2 size;
	bool overlap;
	ResourceID id[2];
	int frame[2];
	vec2 spriteOffset[2];
	int layerCount;
	bool flipped;
	
};