#pragma once
#include <vec2.h>
#include <ResourceID.h>

struct HUDText {
	//vec2 pos;
	//vec2 scale;
	//ResourceID resourceId;
	char text[100];
	vec2 pos;
	int scale;
	bool isStatic = true;
	bool background = false;
};