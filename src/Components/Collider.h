#pragma once

#include <vec2.h>

struct Collider {

	Collider() :
		pos(vec2(0,0)),
		size(vec2(0,0)),
		overlap(false)
	{}

	Collider(const vec2& pos, vec2 size) :
		pos(pos),
		size(size),
		overlap(false)
	{ }


	const vec2& pos;
	vec2 size;
	bool overlap;
};