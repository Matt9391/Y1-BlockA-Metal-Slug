#pragma once

#include <vec2.h>

class RigidBody {
public:

	RigidBody(const vec2& pos, bool hasGravity);

private:

	static const float gravity;

	const vec2& pos;
	vec2 velocity;

	bool hasGravity;
	bool isGrounded;
};