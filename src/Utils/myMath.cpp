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
}