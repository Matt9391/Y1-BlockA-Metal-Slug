#include "precomp.h"
#include "AnimatedDecoration.h"

AnimatedDecoration::AnimatedDecoration() {}

AnimatedDecoration::AnimatedDecoration(AnimationSet set, vec2 pos, int layer) :
    renderData(set, pos, layer)
    {
        animator.setAnimation(&renderData.animationSet);
    }

AnimatedDecoration::AnimatedDecoration(const AnimatedDecoration &other) :
    renderData(other.renderData)
    {
        animator.setAnimation(&renderData.animationSet);
    }


    AnimatedDecoration& AnimatedDecoration::operator=(const AnimatedDecoration& other)
{
    if (this != &other)
    {
        renderData = other.renderData;
        animator.setAnimation(&renderData.animationSet);
    }

    return *this;
}

void AnimatedDecoration::update(float dt){
    animator.playAnimation(dt);
}
RenderData AnimatedDecoration::getRenderData() const{
    return this->renderData;
}
