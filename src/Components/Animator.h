#pragma once

#include <vec2.h>
#include <AnimationSet.h>

class Tmpl8::Surface;

class Animator
{
public:
	Animator();

	bool setAnimation(AnimationSet* newAnimationSet, bool flipped = false, bool reset = false);

	bool isAnimationEnded() const;
	void playAnimation(float dt);
private:
	AnimationSet* animationSet;

	float timeElapsed[MAX_LAYERS];
	bool animationEnded;
};

