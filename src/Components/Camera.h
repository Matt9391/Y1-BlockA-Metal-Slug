// Camera - the scrolling view over the level. It follows the player horizontally (and vertically near
// the boss) and is clamped to the world size, so it never shows anything outside the map.
#pragma once

#include <vec2.h>


class Camera
{
public:
	Camera(vec2 pos, vec2 size);

	void init(vec2 pos_); // place the camera at a position
	void follow(const vec2& target, float dt); // move toward the target, call once per frame

	vec2 getPos() const; // top-left of the view in world space, or (0,0) when the camera is disabled

	void setWorldSize(const vec2& worldSize_); // area the camera may scroll in; also resets the Y limits

	void enableYFollow(bool enabled); // let the camera also follow the target vertically
	void enableCamera(bool enabled_); // disabled = getPos() always returns (0,0) (used by the menus)

	void setMinYLimit(float minY_); // highest point (smallest y) the camera may scroll to

	bool isOutOfView(const vec2& pos_) const; // true if pos is outside the view grown by 'threshold' on every side

	vec2 getMin() const; // top-left corner of the view
	vec2 getMax() const; // bottom-right corner of the view

private:
	vec2 pos;
	vec2 size; // view size (= screen size)
	vec2 worldSize; // scrollable area; it grows when the helicopter is destroyed

	const vec2 threshold; // extra margin used by isOutOfView()
	
	bool enable;
	bool followY;

	float minY;
	float maxY; // lowest point the camera may scroll to (eased toward its target in follow())
};