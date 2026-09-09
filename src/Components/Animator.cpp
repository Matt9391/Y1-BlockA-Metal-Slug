#include "precomp.h"
#include "Animator.h"

#include <AnimationSet.h>


Animator::Animator(vec2 pos):
	animationSet(nullptr),
	pos(pos),
	timeElapsed{ 0.f }
	{

	}


//Added bool return value so you its possible to check whether the animation has been set or not
bool Animator::setAnimation(AnimationSet* newAnimationSet, bool reset) {
	if (this->animationSet == nullptr || reset) {
		this->animationSet = newAnimationSet;

		for (int i = 0; i < animationSet->layerCount; i++) {
			animationSet->layers[i].currentFrame = 0;
		}

		return true;
	}

	if (*this->animationSet == *newAnimationSet) return false;

	this->animationSet = newAnimationSet;

	for (int i = 0; i < animationSet->layerCount; i++) {
		animationSet->layers[i].currentFrame = 0;
	}

	return true;
}


void Animator::playAnimation(float dt) {
	if (animationSet == nullptr) {
		throw runtime_error("Impossible to run animation before setting one");
	}
	
	for (int i = 0; i < animationSet->layerCount; i++) {
		AnimationLayer& l = animationSet->layers[i];

		this->timeElapsed[i] += dt;
		if (timeElapsed[i] >= l.frameDuration) {
			timeElapsed[i] = 0.f;
			//l.currentFrame = 0;
			l.currentFrame = ++l.currentFrame % l.nFrames;
		}


	}
}