#pragma once
#include <vec2.h>
#include <Animator.h>
#include <RenderSet.h>


class Tmpl8::Surface;
class ResourceManager;

class Entity
{
public:
	Entity(vec2 pos);
	virtual ~Entity() = default;

	virtual void loadGFX() = 0;

	vec2 getPos() const;
	RenderSet getRenderSet() const;

	virtual void update(float dt);

protected:
	Animator& getAnimator();
	AnimationSet*& getAnimationSets();

	void setPos(const vec2& newPos);
	void addToPos(const vec2& newPos);
	
	int getCurrentASIndex() const;
	void setCurrentASIndex(int nextASIndex);

private:

	vec2 pos;
	vec2 velocity;
	//Collider collider;
	Animator animator;
	AnimationSet* animationSets;
	//Current Animation Set Index
	int currentASIndex;
};

