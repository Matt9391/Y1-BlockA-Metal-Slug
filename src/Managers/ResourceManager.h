#pragma once

#include <ResourceID.h>
#include <Map.h>


class Tmpl8::Sprite;


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void init();

	Sprite* getSprite(ResourceID resourceId) const;
	const Map& getMap() const; 
private:
	bool initalized;

	Sprite* sprites[ResourceID::ID_COUNTS];
	Map map;
};
