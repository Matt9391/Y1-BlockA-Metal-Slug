#pragma once
#include <vec2.h>
#include <Animator.h>


class Tmpl8::Surface;
class ResourceManager;

class Entity
{
public:
	Entity(vec2 pos);

	virtual void loadGFX(ResourceManager& resourceManager) = 0;

	virtual void update(float dt);

	virtual void display(float dt, Surface* screen);

protected:

	vec2 pos;
	vec2 velocity;
	//Collider collider;
	Animator animator;

};

