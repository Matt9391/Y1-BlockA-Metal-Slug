#pragma once

// AnimatedDecoration - a looping animation placed in the world that does nothing else
// (the waterfalls and the animated water in the GameScene). It owns its RenderData and an Animator.

#include <RenderData.h>
#include <Animator.h>

class AnimatedDecoration {
public:
    AnimatedDecoration(AnimationSet set, vec2 pos, int layer);
    AnimatedDecoration();
    // The Animator points at OUR renderData.animationSet, so copying needs custom code to re-point it
    // at the new object's copy (otherwise it would keep pointing into the object it was copied from).
    AnimatedDecoration(const AnimatedDecoration &other);
    
    AnimatedDecoration& operator=(const AnimatedDecoration& other);
    
    void update(float dt);
    RenderData getRenderData() const;

private:
    RenderData renderData; 
    Animator animator;
};