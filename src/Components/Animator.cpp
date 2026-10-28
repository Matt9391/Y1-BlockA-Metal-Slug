#include "precomp.h"
#include "Animator.h"

#include <AnimationSet.h>
#include <cstdio>
#include <cstdlib>


Animator::Animator():
	animationSet(nullptr),
	timeElapsed{ 0.f },
	animationEnded(false)
	{

	}


//Added bool return value so you its possible to check whether the animation has been set or not
bool Animator::setAnimation(AnimationSet* newAnimationSet, bool flipped,  bool reset) {
	bool result = false;
	// First animation ever, or a forced restart: (re)start from frame 0.
	if (this->animationSet == nullptr || reset) {
		this->animationSet = newAnimationSet;

		for (int i = 0; i < animationSet->layerCount; i++) {
			animationSet->layers[i].currentFrame = 0;
		}
		animationEnded = false;

		result = true;
	}
	else {

		// Same content as the animation already playing: keep playing it without restarting.
		// (Note: in this case the pointer is not updated, the Animator keeps using the old set.)
		if (*this->animationSet == *newAnimationSet) {
			result = false;
		}
		else {

			// Different animation: point to it and restart every layer from frame 0.
			this->animationSet = newAnimationSet;
			
			this->animationEnded = false;

			for (int i = 0; i < animationSet->layerCount; i++) {
				animationSet->layers[i].currentFrame = 0;
			}
			result = true;
		}
	}
	this->animationSet->flipped = flipped;

	return result;
}

bool Animator::isAnimationEnded() const {
	return this->animationEnded;
}

void Animator::setFrame(int frame){
	if (this->animationSet == nullptr) return;

	for (int i = 0; i < animationSet->layerCount; i++) {
		animationSet->layers[i].currentFrame = frame;
	}
}


void Animator::playAnimation(float dt) {
	if (animationSet == nullptr) {
		printf("Impossible to run animation before setting one\n");
		abort();
	}
	
	// Every layer has its own timer, so layers with different frame durations animate independently.
	for (int i = 0; i < animationSet->layerCount; i++) {
		AnimationLayer& l = animationSet->layers[i];

		this->timeElapsed[i] += dt;
		if (this->timeElapsed[i] >= l.frameDuration) {
			this->timeElapsed[i] = 0.f;
			l.currentFrame = ++l.currentFrame % l.nFrames; // next frame, wrapping back to 0 after the last one
		}

		// "Ended" = sitting on the last frame. It is overwritten for each layer, so with 2 layers the LAST layer decides.
		this->animationEnded = l.currentFrame == (l.nFrames -1);

	}
}