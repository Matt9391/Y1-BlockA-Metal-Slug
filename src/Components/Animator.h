// Animator - plays an AnimationSet: advances the currentFrame of every layer based on elapsed time.
// It does NOT own the AnimationSet, it only points to one stored in the entity.
#pragma once

#include <vec2.h>
#include <AnimationSet.h>

class Tmpl8::Surface;

class Animator
{
public:
	Animator();

	// Switch to an animation. The frames restart from 0 only if it is a different animation (or reset = true).
	// Returns true if the animation was (re)started.
	bool setAnimation(AnimationSet* newAnimationSet, bool flipped = false, bool reset = false);

	bool isAnimationEnded() const; // true while the current animation sits on its last frame
	void setFrame(int frame); // force every layer to one frame (used by direction-based sprites, e.g. bullets and the tank turret)
	void playAnimation(float dt); // advance the frames by dt (ms)
private:
	AnimationSet* animationSet;

	float timeElapsed[MAX_LAYERS]; // per-layer timer since that layer's last frame change
	bool animationEnded;
};

