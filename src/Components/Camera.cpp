#include "precomp.h"
#include "Camera.h"
#include <myMath.h>


Camera::Camera(vec2 pos, vec2 size) :
	pos(pos),
	size(size),
	worldSize(0,0)
	{}


void Camera::follow(const vec2& target) {
	// "-this->size / 2" because the pivot (of the camera) is in the top-left corner
	this->pos.x = target.x - this->size.x / 2;
	this->pos.y = target.y - this->size.y / 2;

	this->pos.x = myMath::constrain(this->pos.x, 0, this->worldSize.x - this->size.x);
	this->pos.y = myMath::constrain(this->pos.y, 0, this->worldSize.y - this->size.y);
}

vec2 Camera::getPos() const {
	return this->pos;
}

void Camera::setWorldSize(const vec2& worldSize) {
	this->worldSize = worldSize;
}