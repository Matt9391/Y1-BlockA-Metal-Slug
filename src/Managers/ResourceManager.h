#pragma once

#include <ResourceID.h>


class Tmpl8::Sprite;


class ResourceManager
{
public:
	ResourceManager();

	void init();

	Sprite* getSprite(ResourceID resourceId) const;

private:
	bool initalized;

	Sprite* sprites[ResourceID::COUNTS];

};
