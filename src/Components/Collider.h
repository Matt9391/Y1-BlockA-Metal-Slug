#pragma once

#include <vec2.h>

struct Collider {

	Collider() :
		pos(vec2(0,0)),
		size(vec2(0,0)),
		offset(vec2(0,0)),
		overlap(false)
	{}

	Collider(const vec2& pos, vec2 size, vec2 offset) :
		pos(pos),
		size(size),
		offset(offset),
		overlap(false)
	{ }

	vec2 offset;
	const vec2& pos;
	vec2 size;
	bool overlap;
};