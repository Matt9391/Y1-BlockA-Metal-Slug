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
bool Animator::setAnimation(AnimationSet* newAnimationSet, bool flipped,  bool reset) {
	bool result = false;
	if (this->animationSet == nullptr || reset) {
		this->animationSet = newAnimationSet;

		for (int i = 0; i < animationSet->layerCount; i++) {
			animationSet->layers[i].currentFrame = 0;
		}

		result = true;
	}
	else {

		if (*this->animationSet == *newAnimationSet) {
			result = false;
		}
		else {

			this->animationSet = newAnimationSet;
			

			for (int i = 0; i < animationSet->layerCount; i++) {
				animationSet->layers[i].currentFrame = 0;
				result = true;
			}
		}
	}
	this->animationSet->flipped = flipped;

	return result;
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
			l.currentFrame = ++l.currentFrame % l.nFrames;
		}


	}
}