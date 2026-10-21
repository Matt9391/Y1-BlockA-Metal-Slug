#pragma once

#include <RenderData.h>
#include <Animator.h>

class AnimatedDecoration {
public:
    AnimatedDecoration(AnimationSet set, vec2 pos, int layer);
    AnimatedDecoration();
    AnimatedDecoration& operator=(const AnimatedDecoration& other);
    AnimatedDecoration(const AnimatedDecoration &other);
    void update(float dt);
    RenderData getRenderData() const;

private:
    RenderData renderData; 
    Animator animator;
};