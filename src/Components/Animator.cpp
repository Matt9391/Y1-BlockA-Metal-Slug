#include "precomp.h"
#include "Animator.h"

#include <AnimationSet.h>


Animator::Animator(vec2 pos):
	animationSet(nullptr),
	pos(pos),
	timeElapsed(0.f)
	{

	}

void Animator::playAnimation(float dt, Surface* screen) {
	for (int i = 0; i < animationSet->layerCount; i++) {
		AnimationLayer& l = animationSet->layers[i];
		
		this->timeElapsed += dt;
		if (timeElapsed >= l.frameDuration) {
			timeElapsed = 0.f;
			l.currentFrame = l.currentFrame++ % l.nFrames;
		}

		l.sprite->SetFrame(l.currentFrame);
		l.sprite->Draw(screen, pos.x, pos.y);
	}
}