#include "precomp.h"
#include "Entity.h"

Entity::Entity(vec2 pos) :
	pos(pos),
	velocity(0,0),
	animator(pos),
	animationSets(nullptr),
	currentASIndex(-1)
	{ }


void Entity::update(float dt) {

}

RenderSet Entity::getRenderSet() const {

	return RenderSet{ animationSets[currentASIndex], pos };
}

void Entity::display(float dt, Surface* screen) {

}