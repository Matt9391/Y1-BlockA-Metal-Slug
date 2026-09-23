#include "precomp.h"
#include "RigidBody.h"

const float RigidBody::gravity = 0.001f;

RigidBody::RigidBody(const vec2& pos, bool hasGravity) :
	pos(pos),
	velocity(0, 0),
	hasGravityVariable(hasGravity),
	isGroundedVariable(false),
	speed(0)
{ }

vec2 RigidBody::getPos() const {
	return pos;
}

vec2 RigidBody::getVelocity() const{
	return this->velocity;
}
void RigidBody::setVelocity(vec2 v, bool overwrite) {
	if(overwrite){
		this->velocity = v;
	}
	else {
		this->velocity.x = v.x != 0 ? v.x : this->velocity.x;
		this->velocity.y = v.y != 0 ? v.y : this->velocity.y;
	}
}

void RigidBody::setVelocityX(float v){
	this->velocity.x = v;
}
void RigidBody::setVelocityY(float v) {
	this->velocity.y = v;
}

void RigidBody::addVelocity(vec2 v) {
	this->velocity += v;
}

void RigidBody::setGrounded(bool grounded) {
	this->isGroundedVariable = grounded;
}

bool RigidBody::isGrounded() const{
	return this->isGroundedVariable;
}
bool RigidBody::hasGravity() const{
	return this->hasGravityVariable;
}


void RigidBody::setSpeed(float s) {
	this->speed = s;
}
float  RigidBody::getSpeed() const {
	return speed;
}

float RigidBody::getGravity() const {
	return this->gravity;
}