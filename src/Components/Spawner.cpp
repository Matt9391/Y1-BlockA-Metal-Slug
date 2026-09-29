#include "precomp.h"
#include "Spawner.h"


Spawner::Spawner(vec2 pos, vec2 size, float spawnDelay) :
	pos(pos),
	size(size),
	spawnDelay(spawnDelay),
	timer(0.f)
{
}

Spawner::~Spawner() {
}

void Spawner::update(float dt) {}


const vec2& Spawner::getPos() const {
	return this->pos;
}
const vec2& Spawner::getSize() const {
	return this->size;
}