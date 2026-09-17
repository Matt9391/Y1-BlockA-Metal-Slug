#pragma once

namespace myMath {

	//constrain the 'value' between min and max values
	float constrain(float value, float min, float max);

	float mapValue(float value, float fromMin, float fromMax, float toMin, float toMax);
}