#pragma once

#include <vec2.h>

class RigidBody {
public:

	RigidBody(const vec2& pos, bool hasGravity); // pos is a reference to the owner's position

	vec2 getPos() const;

	vec2 getVelocity() const;
	//overwrite is to be able to set only component, if you pass (1,0) it only set the x component without overwriting the y since its 0
	void setVelocity(vec2 v, bool overwrite = false);
	void setVelocityX(float v);
	void setVelocityY(float v);
	void addVelocity(vec2 v);

	void setGrounded(bool grounded);
	bool isGrounded() const;

	void setSpeed(float s); // movement speed in px/ms; entities multiply it by their direction
	float getSpeed() const;
	
	//void setGravity(float g);
	float getGravity() const; // gravity acceleration in px/ms^2
	float getJumpForce() const; // upward velocity given when jumping, in px/ms


private:

	static const float gravity; // shared by every RigidBody
	static const float jumpForce;

	const vec2& pos;
	vec2 velocity;
	float speed;

	bool isGroundedVariable;
	bool hasGravityVariable;
};