#include "precomp.h"
#include "Entity.h"
#include <RigidBody.h>

Entity::Entity(vec2 pos, bool needsRigidBody) :
	pos(pos),
	velocity(0,0),
	dir(0,0),
	lastDir(0,0),
	animator(pos),
	animationSets(nullptr),
	currentASIndex(-1),
	collider(this->pos, vec2(0,0), vec2(0,0)),
	rigidBody(nullptr)
	{
		this->rigidBody = needsRigidBody ? new RigidBody(this->pos, true) : nullptr;

	}

Entity::~Entity()
{
	delete rigidBody;
}
void Entity::update(float dt) {
}

RenderSet Entity::getRenderSet() const {
	return RenderSet{ animationSets[currentASIndex], pos };
}

const vec2& Entity::getPos() const{
	return this->pos;
}

vec2 Entity::getVelocity() const {
	if (getRigidBody() == nullptr) return vec2(0, 0);
	return getRigidBody()->getVelocity();
}

void Entity::setVelocity(vec2 v) {
	this->getRigidBody()->setVelocity(v);
}


void Entity::addVelocity(vec2 v) {
	this->getRigidBody()->addVelocity(v);
}

void Entity::setVelocityX(float v) { rigidBody->setVelocityX(v); }
void Entity::setVelocityY(float v) { rigidBody->setVelocityY(v); }

Animator& Entity::getAnimator(){
	return this->animator;
}
AnimationSet*& Entity::getAnimationSets() {
	return this->animationSets;
}

void Entity::setPos(const vec2& newPos) {
	this->pos = newPos;
}

void Entity::setCollider(vec2 size, vec2 offset) {
	this->collider.offset = offset;
	this->collider.size= size;
}
void Entity::setColliderOffset(vec2 offset) {
	this->collider.offset = offset;
}

void Entity::addToPos(const vec2& newPos) {
	this->pos += newPos;
}

void Entity::setGrounded(bool grounded) {
	if (rigidBody) {
		rigidBody->setGrounded(grounded);
		//if (grounded) {
		//	rigidBody->setVelocityY(0.f);
		//}
	}
}

int Entity::getCurrentASIndex() const {
	return this->currentASIndex;
}

void Entity::setCurrentASIndex(int nextASIndex) {
	this->currentASIndex = nextASIndex;
}

vec2 Entity::getDir() const {
	return this->dir;
}
vec2 Entity::getLastDir() const {
	return this->lastDir;
}

void Entity::setDir(vec2 dir){
	this->dir = dir;
}
void Entity::setLastDir(vec2 dir) {
	this->lastDir = dir;
}


Collider& Entity::getCollider() {
	return this->collider;
}

RigidBody* Entity::getRigidBody() const {
	return this->rigidBody;
}
