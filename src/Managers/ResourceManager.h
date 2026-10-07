#pragma once

#include <ResourceID.h>
#include <Map.h>
#include <SoundID.h>


class Tmpl8::Sprite;


class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void init();

	Sprite* getSprite(ResourceID resourceId) const;
	const char* getSoundPath(SoundID soundId) const;
	const Map& getMap() const; 
private:
	bool initalized;

	Sprite* sprites[ResourceID::ID_COUNTS];
	char* soundPaths[SoundID::SID_COUNTS];
	Map map;
};
