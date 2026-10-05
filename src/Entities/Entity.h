#pragma once
#include <vec2.h>
#include <Animator.h>
#include <RenderContainer.h>
#include <Collider.h>


class Tmpl8::Surface;
class ResourceManager;
class RigidBody;

enum EntityType {
	ET_PLAYER,
	ET_REBELSOLDIER,
	ET_POW,
	ET_GRANADE,
	ET_BULLET,
	ET_LOOTDROP,
	ET_POWERUP,
	ET_COUNTS
};


class Entity
{
public:
	Entity(vec2 pos, bool needsRigidBody, EntityType entityType);
	virtual ~Entity();

	virtual void loadGFX() = 0;

	const vec2& getPos() const;

	const Collider& getCollider() const;
	void addToPos(const vec2& newPos);
	void setPos(const vec2& newPos);

	void setGrounded(bool grounded);

	RenderContainer getRenderContainer() const;

	void setVelocity(vec2 v) ;
	vec2 getVelocity() const;

	void setVelocityX(float v);
	void setVelocityY(float v);
	void addVelocity(vec2 v);
	virtual void update(float dt);


	vec2 getLastDir() const;
	vec2 getDir() const;
	void setDir(vec2 dir_);

	RigidBody* getRigidBody() const;

	bool hasToBeFreed() const;

	EntityType getEntityType() const;
protected:
	Animator& getAnimator();
	const Animator& getAnimator() const;
	AnimationSet*& getAnimationSets();

	
	void setCollider(vec2 size, vec2 offset);
	void setColliderOffset(vec2 offset);
	int getCurrentASIndex() const;
	void setCurrentASIndex(int nextASIndex);

	
	void setLastDir(vec2 dir_);

	void setFree(bool free_);

private:

	vec2 pos;
	vec2 dir;
	vec2 lastDir;
	//Collider collider;
	Animator animator;
	AnimationSet* animationSets;
	//Current Animation Set Index
	int currentASIndex;

	Collider collider;
	RigidBody* rigidBody;
	EntityType entityType;

	bool free;

};

