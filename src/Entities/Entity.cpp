#include "precomp.h"
#include "Entity.h"
#include <RigidBody.h>

Entity::Entity(vec2 pos, bool needsRigidBody) :
	pos(pos),
	velocity(0,0),
	animator(pos),
	animationSets(nullptr),
	currentASIndex(-1),
	collider(this->pos, vec2(30,30)),
	rigidBody(nullptr)
	{
		this->rigidBody = needsRigidBody ? new RigidBody(this->pos, true) : nullptr;
	}


void Entity::update(float dt) {

}

RenderSet Entity::getRenderSet() const {
	return RenderSet{ animationSets[currentASIndex], pos };
}

vec2 Entity::getPos() const {
	return this->pos;
}

Animator& Entity::getAnimator(){
	return this->animator;
}
AnimationSet*& Entity::getAnimationSets() {
	return this->animationSets;
}

void Entity::setPos(const vec2& newPos) {
	this->pos = newPos;
}

void Entity::addToPos(const vec2& newPos) {
	this->pos += newPos;
}

int Entity::getCurrentASIndex() const {
	return this->currentASIndex;
}

void Entity::setCurrentASIndex(int nextASIndex) {
	this->currentASIndex = nextASIndex;
}

Collider& Entity::getCollider() {
	return this->collider;
}

RigidBody* Entity::getRigidBody() const {
	return this->rigidBody;
}
