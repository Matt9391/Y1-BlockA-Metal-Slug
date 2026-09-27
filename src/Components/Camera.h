#pragma once

#include <vec2.h>


class Camera
{
public:
	Camera(vec2 pos, vec2 size);

	void follow(const vec2& target);

	vec2 getPos() const;

	void setWorldSize(const vec2& worldSize);

	void enableYFollow(bool enabled);
	void enableCamera(bool enabled);

	void setMinYLimit(float minY);

private:
	vec2 pos;
	vec2 size;
	vec2 worldSize;

	bool enable;
	bool followY;

	float minY;
	float maxY;
};