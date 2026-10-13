#include "precomp.h"
#include "Animator.h"

#include <AnimationSet.h>


Animator::Animator():
	animationSet(nullptr),
	timeElapsed{ 0.f },
	animationEnded(false),
	longestLayer(0)
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
		animationEnded = false;

		result = true;
	}
	else {

		if (*this->animationSet == *newAnimationSet) {
			result = false;
		}
		else {

			this->animationSet = newAnimationSet;
			
			this->animationEnded = false;

			for (int i = 0; i < animationSet->layerCount; i++) {
				animationSet->layers[i].currentFrame = 0;
			}
			result = true;
		}
	}
	this->animationSet->flipped = flipped;

	if (result) {
		longestLayer = 0;
		for (int i = 1; i < animationSet->layerCount; i++) {
			if (animationSet->layers[i].nFrames > animationSet->layers[longestLayer].nFrames) {
				longestLayer = i;
			}
		}
	}

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
		throw runtime_error("Impossible to run animation before setting one");
	}
	
	for (int i = 0; i < animationSet->layerCount; i++) {
		AnimationLayer& l = animationSet->layers[i];

		this->timeElapsed[i] += dt;
		if (this->timeElapsed[i] >= l.frameDuration) {
			this->timeElapsed[i] = 0.f;
			l.currentFrame = ++l.currentFrame % l.nFrames;
		}
	}
	
	this->animationEnded = animationSet->layers[longestLayer].currentFrame == (animationSet->layers[longestLayer].nFrames - 1);

	
}