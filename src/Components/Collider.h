#pragma once

#include <vec2.h>
#include <ResourceID.h>

#define MAXLAYER 2

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
		flipped(false),
		radius(500.f)
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
		flipped(false),
		radius(500.f)
	{ }

	vec2 offset;
	const vec2& pos;
	vec2 size;
	bool overlap;
	float radius;
	ResourceID id[MAXLAYER];
	int frame[MAXLAYER];
	vec2 spriteOffset[MAXLAYER];
	int layerCount;
	bool flipped;
	
};