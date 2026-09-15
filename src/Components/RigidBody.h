#pragma once

#include <vec2.h>

class RigidBody {
public:

	RigidBody(const vec2& pos, bool hasGravity);

	vec2 getPos() const;

	vec2 getVelocity() const;
	//overwrite is to be able to set only component, if you pass (1,0) it only set the x component without overwriting the y since its 0
	void setVelocity(vec2 v, bool overwrite = false);
	void addVelocity(vec2 v);

	void setGrounded(bool grounded);
	bool isGrounded() const;
	bool hasGravity() const;

private:

	static const float gravity;

	const vec2& pos;
	vec2 velocity;

	bool isGroundedVariable;
	bool hasGravityVariable;
};