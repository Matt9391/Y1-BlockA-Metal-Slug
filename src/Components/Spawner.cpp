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

void Spawner::update(float) {
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

void Spawner::setSpawnDelay(float spawnDelay_) {
    this->spawnDelay = spawnDelay_;
}

float Spawner::getTimer() const {
    return timer;
}

void Spawner::setTimer(float timer_) {
    this->timer = timer_;
}

void Spawner::addTimer(float dt){
    this->timer += dt;
}

float Spawner::getDistToPlayer() const {
    return distToPlayer;
}

void Spawner::setDistToPlayer(float distToPlayer_) {
    this->distToPlayer = distToPlayer_;
}

bool Spawner::getSpawnEntity() const {
	return this->spawnEntity;
}
void Spawner::setSpawnEntity(bool spawnEntity_) {
	this->spawnEntity = spawnEntity_;
}

int  Spawner::getSpawnedNumber() const {
	return this->spawnedNumber;
}
void Spawner::addSpawnedNumber() {
	this->spawnedNumber++;
}
