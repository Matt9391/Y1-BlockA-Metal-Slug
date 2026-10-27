#include "precomp.h"
#include "myMath.h"
#include "vec2.h"

namespace myMath {
	//constrain the 'value' between min and max values
	float constrain(float value, float min, float max) {
		if (value < min)
			return min;
		if (value > max)
			return max;
		return value;
	}
	

	float mapValue(float value, float fromMin, float fromMax, float toMin, float toMax) {
		return (value - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
	}

	float lerp(float a, float b, float t){
		return a + (b - a) * t;
	}

	float DistanceSquared(const vec2& a, const vec2& b) {
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return dx * dx + dy * dy;
	}
}