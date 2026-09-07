#include "precomp.h"
#include "Animator.h"

#include <AnimationSet.h>


Animator::Animator(vec2 pos):
	animationSet(nullptr),
	pos(pos),
	timeElapsed(0.f)
	{

	}


void Animator::setAnimation(AnimationSet* newAnimationSet) {
	this->animationSet = newAnimationSet;
}


void Animator::playAnimation(float dt, Surface* screen) {
	if (animationSet == nullptr) {
		throw new runtime_error("Impossible to run animation before setting one");
	}
	
	for (int i = 0; i < animationSet->layerCount; i++) {
		AnimationLayer& l = animationSet->layers[i];
		
		if (l.sprite == nullptr) {
			throw new runtime_error("Impossible to read sprite data");
		}

		this->timeElapsed += dt;
		if (timeElapsed >= l.frameDuration) {
			timeElapsed = 0.f;
			l.currentFrame = ++l.currentFrame % l.nFrames;
		}

		l.sprite->SetFrame(l.currentFrame);
		//l.sprite->Draw(screen, pos.x + l.offset.x, pos.y + l.offset.y);
		l.sprite->DrawScaled(pos.x + l.offset.x, pos.y + l.offset.y, l.sprite->GetWidth() * 3, l.sprite->GetHeight() * 3, screen);
	}
}