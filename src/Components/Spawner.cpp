#include "precomp.h"
#include "Spawner.h"


Spawner::Spawner(vec2 pos, vec2 size, float spawnDelay) :
	pos(pos),
	size(size),
	spawnDelay(spawnDelay),
	timer(0.f),
	distToPlayer(CL_MAXFLOAT),
	spawnEntity(false),
	spawnedNumber(0)
{
}

Spawner::~Spawner() {

}

void Spawner::update(float dt) {
}


const vec2& Spawner::getPos() const {
	return this->pos;
}
const vec2& Spawner::getSize() const {
	return this->size;
}


float Spawner::getSpawnDelay() const {
    return spawnDelay;
}

void Spawner::setSpawnDelay(float spawnDelay) {
    this->spawnDelay = spawnDelay;
}

float Spawner::getTimer() const {
    return timer;
}

void Spawner::setTimer(float timer) {
    this->timer = timer;
}

void Spawner::addTimer(float dt){
    this->timer += dt;
}

float Spawner::getDistToPlayer() const {
    return distToPlayer;
}

void Spawner::setDistToPlayer(float distToPlayer) {
    this->distToPlayer = distToPlayer;
}

bool Spawner::getSpawnEntity() const {
	return this->spawnEntity;
}
void Spawner::setSpawnEntity(bool spawnEntity) {
	this->spawnEntity = spawnEntity;
}

int  Spawner::getSpawnedNumber() const {
	return this->spawnedNumber;
}
void Spawner::addSpawnedNumber() {
	this->spawnedNumber++;
}
