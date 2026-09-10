#pragma once

#include <vec2.h>


class Camera {

public:
	Camera(vec2 pos, vec2 size);

	void follow(const vec2& pos);

	vec2 getPos() const;

	void setWorldSize(const vec2& worldSize);
private:
	vec2 pos;
	vec2 size;
	vec2 worldSize;

};