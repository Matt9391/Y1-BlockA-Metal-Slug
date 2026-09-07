#pragma once

#include <vec2.h>

class AnimationSet;
class Tmpl8::Surface;

class Animator
{
public:
	Animator(vec2 pos);

	void setAnimation(AnimationSet* animationSet);

	void playAnimation(float dt, Surface* screen);
private:
	AnimationSet* animationSet;
	vec2 pos;

	float timeElapsed;
};

