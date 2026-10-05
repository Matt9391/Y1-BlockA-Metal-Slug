#pragma once

#include <vec2.h>


class Camera
{
public:
	Camera(vec2 pos, vec2 size);

	void init(vec2 pos_);
	void follow(const vec2& target);

	vec2 getPos() const;

	void setWorldSize(const vec2& worldSize_);

	void enableYFollow(bool enabled);
	void enableCamera(bool enabled_);

	void setMinYLimit(float minY_);

	bool isOutOfView(const vec2& pos_) const;

private:
	vec2 pos;
	vec2 size;
	vec2 worldSize;

	const vec2 threshold;
	
	bool enable;
	bool followY;

	float minY;
	float maxY;
};