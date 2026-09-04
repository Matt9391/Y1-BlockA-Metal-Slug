#pragma once

#include <ResourceID.h>


class Tmpl8::Sprite;


class ResourceManager
{
public:
	ResourceManager();

	Sprite* getSprite(ResourceID resourceId);

private:

	Sprite* sprites[ResourceID::COUNTS];

};
