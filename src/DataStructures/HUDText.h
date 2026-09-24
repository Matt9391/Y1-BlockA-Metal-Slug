#pragma once
#include <vec2.h>
#include <ResourceID.h>

struct HUDText {

	//vec2 scale;
	ResourceID resourceId;
	char text[50];
	vec2 pos;
	float scale;

	HUDText(ResourceID id, const char* str, vec2 p, float s)
		: resourceId(id), pos(p), scale(s)
	{
		snprintf(text, sizeof(text), "%s", str);
	}
	
	HUDText()
		: resourceId(ResourceID::ID_NULL), 
		pos(0,0), 
		scale(1.f),
		text("")
	{
	}
};