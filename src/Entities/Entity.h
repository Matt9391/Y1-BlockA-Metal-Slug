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

	RenderSet getRenderSet() const;

	virtual void update(float dt);

	virtual void display(float dt, Surface* screen);

protected:

	vec2 pos;
	vec2 velocity;
	//Collider collider;
	Animator animator;
	AnimationSet* animationSets;
	//Current Animation Set Index
	int currentASIndex;
};

