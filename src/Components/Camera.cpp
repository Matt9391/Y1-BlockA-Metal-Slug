#include "precomp.h"
#include "Camera.h"
#include <myMath.h>
#include <iostream>

Camera::Camera(vec2 pos, vec2 size) :
	pos(pos),
	size(size),
	worldSize(0, 0),
	enable(false),
	followY(false),
	minY(0),
	maxY(0),
	threshold(vec2(100,100))
{
}

void Camera::init(vec2 pos_) {
	this->pos = pos_;
}


void Camera::follow(const vec2& target, float dt)
{

	const float followPointX = this->size.x * 0.20f; // 20% of screen

	// Only scroll when the target walks past that point. There is no "else": the camera never scrolls back left.
	if (target.x > pos.x + followPointX)
    {
        float wantedX = target.x - followPointX; // keep the target at 20% of the screen width

        pos.x = myMath::lerp(pos.x, wantedX, dt * 0.006f); // DONE: should need dt
    }

	// Never show anything outside the world horizontally.
	this->pos.x = myMath::constrain(this->pos.x,0,this->worldSize.x - this->size.x);


	// Boss area (camera past x = 3300): it also follows vertically and may go 30 px above the top of the map.
	if (this->pos.x > 3300) {
		enableYFollow(true);
		setMinYLimit(-30);
	}

	const float worldMaxY = this->worldSize.y - this->size.y;

	// How far down the camera is normally allowed to scroll. Past x = 3300 the bound is
	// lifted by 110 px so the boss stays framed.
	const float targetMaxY = (this->pos.x > 3300) ? (worldMaxY - 110.f) : worldMaxY;

	
	// Safety: the camera must always be allowed to go low enough to show the target with 60 px of space under it.
	const float bottomMargin = 60.f;
	const float playerMaxY = fminf(target.y + bottomMargin - this->size.y, worldMaxY);

	this->maxY = myMath::lerp(this->maxY, targetMaxY, dt * 0.0008f); // ease the bound itself, same rate as position
	this->maxY = fmaxf(this->maxY, playerMaxY);                      // hard floor: the ease may lag, the player may not

	this->pos.y = myMath::constrain(this->pos.y, this->minY, this->maxY);

		

	// Vertical follow (only in the boss area): keep the target in the middle of the screen.
	if (this->followY)
	{
		float wantedY = target.y - this->size.y / 2;
		this->pos.y = myMath::lerp(this->pos.y, wantedY, dt * 0.006f);

		this->pos.y = myMath::constrain(this->pos.y, this->minY, this->maxY);
	}
}

vec2 Camera::getPos() const {
	return enable ? vec2(pos.x, floorf(pos.y)) : vec2(0, 0); // y is floored to a whole pixel
}

void Camera::setWorldSize(const vec2& worldSize_)
{
	this->worldSize = worldSize_;

	// Default Y limits.
	this->minY = 0;
	this->maxY = worldSize.y - this->size.y ;
}

void Camera::enableYFollow(bool enabled)
{
	this->followY = enabled;
}
void Camera::enableCamera(bool enabled_)
{
	this->enable = enabled_;
}

void Camera::setMinYLimit(float minY_)
{
	this->minY = minY_;
}

bool Camera::isOutOfView(const vec2& pos_) const{
	// Convert to screen space and test against the screen rectangle grown by 'threshold' on every side.
	vec2 screenPos = pos_ - this->pos;
	//trick learnt from Jacco :b
	if (screenPos.x < -threshold.x || screenPos.x > SCRWIDTH + threshold.x) return true;
	if (screenPos.y < -threshold.y || screenPos.y > SCRHEIGHT + threshold.y) return true;

	return false;
}


vec2 Camera::getMin() const{
	return this->pos;
}
vec2 Camera::getMax() const{
	return this->pos + this->size;
}