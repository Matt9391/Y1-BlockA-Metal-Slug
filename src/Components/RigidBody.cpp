#include "precomp.h"
#include "RigidBody.h"

const float RigidBody::gravity = 1.f;

RigidBody::RigidBody(const vec2& pos, bool hasGravity) :
	pos(pos),
	velocity(0,0),
	hasGravity(hasGravity),
	isGrounded(false)
{ }

