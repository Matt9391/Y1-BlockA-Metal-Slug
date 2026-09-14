#pragma once

#include <vec2.h>

struct Collider {
	vec2 pos;
	vec2 size;
	bool overlap;
};