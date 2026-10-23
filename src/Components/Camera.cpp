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

	if (target.x > pos.x + followPointX)
    {
        float wantedX = target.x - followPointX;

        pos.x = myMath::lerp(pos.x, wantedX, dt * 0.006f); // DONE: should need dt
    }

	this->pos.x = myMath::constrain(this->pos.x,0,this->worldSize.x - this->size.x);


	if (this->pos.x > 800) {
		enableYFollow(true);
		setMinYLimit(-30);
	}

	float targetMaxY = (this->pos.x > 3300) ? (worldSize.y - size.y - 110.f) : (worldSize.y - size.y);
	this->maxY = myMath::lerp(this->maxY, targetMaxY, dt * 0.0008f); // ease the bound itself, same rate as position

	this->pos.y = myMath::constrain(this->pos.y, this->minY, this->maxY);

		

	if (this->followY)
	{
		float wantedY = target.y - this->size.y / 2;
		this->pos.y = myMath::lerp(this->pos.y, wantedY, dt * 0.006f);

		this->pos.y = myMath::constrain(this->pos.y, this->minY, this->maxY);
	}
}

vec2 Camera::getPos() const {
	return enable ? vec2(pos.x, floorf(pos.y)) : vec2(0, 0);
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
