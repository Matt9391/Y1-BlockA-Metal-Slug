#pragma once

#include <vec2.h>
#include <AnimationSet.h>

class Tmpl8::Surface;

class Animator
{
public:
	Animator(vec2 pos);

	bool setAnimation(AnimationSet* newAnimationSet, bool reset = false);

	void playAnimation(float dt);
private:
	AnimationSet* animationSet;
	vec2 pos;

	float timeElapsed[MAX_LAYERS];
};

