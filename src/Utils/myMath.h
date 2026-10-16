#pragma once

struct vec2;

namespace myMath {

	//constrain the 'value' between min and max values
	float constrain(float value, float min, float max);

	float mapValue(float value, float fromMin, float fromMax, float toMin, float toMax);

	float lerp(float a, float b, float t);

	float DistanceSquared(const vec2& a, const vec2& b);
}