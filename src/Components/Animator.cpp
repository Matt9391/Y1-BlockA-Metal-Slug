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


void Animator::playAnimation(float dt, Surface* screen) {
	if (animationSet == nullptr) {
		throw runtime_error("Impossible to run animation before setting one");
	}
	
	for (int i = 0; i < animationSet->layerCount; i++) {
		AnimationLayer& l = animationSet->layers[i];
		
		if (l.sprite == nullptr) {
			throw runtime_error("Impossible to read sprite data");
		}

		this->timeElapsed[i] += dt;
		if (timeElapsed[i] >= l.frameDuration) {
			timeElapsed[i] = 0.f;
			l.currentFrame = ++l.currentFrame % l.nFrames;
		}

		l.sprite->SetFrame(l.currentFrame);
		l.sprite->Draw(screen, pos.x + l.offset.x, pos.y + l.offset.y);
		l.sprite->DrawScaled(screen, pos.x + l.offset.x, 50 +  pos.y + l.offset.y, 6);
		//l.sprite->DrawScaled(pos.x + l.offset.x, pos.y + l.offset.y, l.sprite->GetWidth() * 3, l.sprite->GetHeight() * 3, screen);
	}
}