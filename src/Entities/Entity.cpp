#include "precomp.h"
#include "Entity.h"
#include <RigidBody.h>
#include <ResourceID.h>
#include <AudioManager.h>

Entity::Entity(vec2 pos, bool needsRigidBody, EntityType entityType) :
	entityType(entityType),
	pos(pos),
	dir(0,0),
	lastDir(0,0),
	animator(),
	animationSets(nullptr),
	currentASIndex(-1),
	collider(this->pos, vec2(0,0), vec2(0,0)),
	rigidBody(nullptr),
	free(false),
	renderLayer(1),
	playerCollisionEnabled(true),
	sounds{SoundID::SID_NULL},
	soundCount(0)
	{
		this->rigidBody = needsRigidBody ? new RigidBody(this->pos, true) : nullptr;

	}

Entity::~Entity()
{
	delete rigidBody;
}
	
void Entity::update(float) {
}

RenderData Entity::getRenderData() const { //make it reference
	return RenderData{ animationSets[currentASIndex], pos, renderLayer };
}

const vec2& Entity::getPos() const{
	return this->pos;
}

vec2 Entity::getVelocity() const {
	if (getRigidBody() == nullptr) return vec2(0, 0);
	return getRigidBody()->getVelocity();
}

void Entity::setVelocity(vec2 v) {
	this->getRigidBody()->setVelocity(v);
}


void Entity::addVelocity(vec2 v) {
	this->getRigidBody()->addVelocity(v);
}

void Entity::setVelocityX(float v) { rigidBody->setVelocityX(v); }
void Entity::setVelocityY(float v) { rigidBody->setVelocityY(v); }

Animator& Entity::getAnimator(){
	return this->animator;
}

const Animator& Entity::getAnimator() const{
	return this->animator;
}
AnimationSet*& Entity::getAnimationSets() {
	return this->animationSets;
}

void Entity::setPos(const vec2& pos_) {
	this->pos = pos_;
}

void Entity::setCollider(vec2 size, vec2 offset) {
	this->collider.offset = offset;
	this->collider.size = size;
	this->collider.radius = (fmaxf(size.x, size.y));
	
}
void Entity::setColliderOffset(vec2 offset) {
	this->collider.offset = offset;
}

void Entity::addToPos(const vec2& newPos) {
	this->pos += newPos;
}

void Entity::setGrounded(bool grounded) {
	if (rigidBody) {
		rigidBody->setGrounded(grounded);
	}
}

int Entity::getCurrentASIndex() const {
	return this->currentASIndex;
}

void Entity::setCurrentASIndex(int nextASIndex) {
	this->currentASIndex = nextASIndex;
}

vec2 Entity::getDir() const {
	return this->dir;
}
vec2 Entity::getLastDir() const {
	return this->lastDir;
}

void Entity::setDir(vec2 dir_){
	this->dir = dir_;
}
void Entity::setLastDir(vec2 dir_) {
	this->lastDir = dir_;
}




const Collider& Entity::getCollider() const {
	return this->collider;
}

RigidBody* Entity::getRigidBody() const {
	return this->rigidBody;
}

void Entity::setFree(bool free_) {
	this->free = free_;
}


bool Entity::hasToBeFreed() const {
	return this->free;
}


EntityType Entity::getEntityType() const {
	return this->entityType;
}

void Entity::setRenderLayer(int renderLayer_){
	this->renderLayer = renderLayer_;
}

void Entity::setColliderSprite(){
	if(animationSets == nullptr) return;
	const AnimationSet& as = animationSets[currentASIndex];
	collider.layerCount = as.layerCount;
	collider.flipped = as.flipped;
	for(int i = 0; i < as.layerCount; i++){
		collider.id[i] = as.layers[i].resourceId;
		collider.frame[i] = as.layers[i].currentFrame;
		collider.spriteOffset[i] = as.flipped ? as.layers[i].offsetFlipped : as.layers[i].offset;
	}
}


void Entity::setRadius(float radius_){
	this->collider.radius = radius_;
}

void Entity::setPlayerCollisionEnabled(bool playerCollisionEnabled_){
	this->playerCollisionEnabled = playerCollisionEnabled_;
}

bool Entity::getPlayerCollisionEnabled() const{
	return this->playerCollisionEnabled;
}


void Entity::addSound(SoundID sid){
	if(sid == SID_NULL) return;
    if(soundCount >= MAXSOUNDS) {
		printf("MAX SOUNDS REACHED, ENTITY");
		return;
    }

	this->sounds[soundCount++] = sid;
}

void Entity::clearSounds(){
	for(int i = 0; i < soundCount; i++){
		this->sounds[i] = SID_NULL;
	}
	soundCount = 0;
}

void Entity::addSoundToManager(AudioManager& am){
	for(int i = 0; i < soundCount; i++){
		am.addAudioToPlay(sounds[i]);
	}
}