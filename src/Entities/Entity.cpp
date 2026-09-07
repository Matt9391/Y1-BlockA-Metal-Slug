#include "precomp.h"
#include "Entity.h"

Entity::Entity(vec2 pos) :
	pos(pos),
	velocity(0,0),
	animator(pos)
	{ }

void Entity::update(float dt) {

}

void Entity::display(float dt, Surface* screen) {

}