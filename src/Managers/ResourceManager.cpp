#include "precomp.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager() :
	sprites{}
	{}

Sprite* ResourceManager::getSprite(ResourceID resourceId) {
	return this->sprites[resourceId];
}
