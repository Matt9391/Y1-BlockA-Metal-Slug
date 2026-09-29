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

void Camera::init(vec2 pos) {
	printf("%.2f, %.2f", this->pos.x, this->pos.y);
	this->pos = pos;
}


void Camera::follow(const vec2& target)
{

	const float followPointX = this->size.x * 0.20f; // 20% of screen

	if (target.x > this->pos.x + followPointX)
	{
		float wantedX = target.x - followPointX;

		if (wantedX > this->pos.x)
			this->pos.x = wantedX;
	}

	this->pos.x = myMath::constrain(this->pos.x,0,this->worldSize.x - this->size.x);


	if (this->pos.x > 500) {
		enableYFollow(true);
		setMinYLimit(-150);
	}

	if (this->followY)
	{
		this->pos.y = target.y - this->size.y / 2;

		this->pos.y = myMath::constrain(this->pos.y,this->minY,this->maxY);
	}
}

vec2 Camera::getPos() const {
	return enable ? vec2(pos.x, floorf(pos.y)) : vec2(0, 0);
}

void Camera::setPos(vec2 pos) {
	this->pos = pos;
}

void Camera::setWorldSize(const vec2& worldSize)
{
	this->worldSize = worldSize;

	// Default Y limits.
	this->minY = 0;
	this->maxY = worldSize.y - this->size.y;
}

void Camera::enableYFollow(bool enabled)
{
	this->followY = enabled;
}
void Camera::enableCamera(bool enabled)
{
	this->enable = enabled;
}

void Camera::setMinYLimit(float minY)
{
	this->minY = minY;
}

bool Camera::isOutOfView(const vec2& pos) const{
	vec2 screenPos = pos - this->pos;
	//trick learnt from Jacco :b
	if (screenPos.x < -threshold.x || screenPos.x > SCRWIDTH + threshold.x) return true;
	if (screenPos.y < -threshold.y || screenPos.y > SCRHEIGHT + threshold.y) return true;

	return false;
}