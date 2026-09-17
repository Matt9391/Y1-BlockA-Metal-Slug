#include "precomp.h"
#include "myMath.h"

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
}