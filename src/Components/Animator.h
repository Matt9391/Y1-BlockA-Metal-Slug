#pragma once

#include <vec2.h>

struct AnimationSet;
class Tmpl8::Surface;

class Animator
{
public:
	Animator(vec2 pos);

	bool setAnimation(AnimationSet* newAnimationSet, bool reset = false);

	void playAnimation(float dt, Surface* screen);
private:
	AnimationSet* animationSet;
	vec2 pos;

	float timeElapsed;
};

