#pragma once
#include <vec2.h>


class Tmpl8::Surface;

class Entity
{
public:
	Entity(vec2 pos);

	virtual void update(float dt);

	virtual void display(Surface* screen);

protected:

	vec2 pos;
	vec2 velocity;
	//Collider collider;
	//Animator animator;

};

