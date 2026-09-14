#pragma once
#include <vec2.h>
#include <Animator.h>
#include <RenderSet.h>
#include <Collider.h>


class Tmpl8::Surface;
class ResourceManager;
class RigidBody;


class Entity
{
public:
	Entity(vec2 pos, bool needsRigidBody);
	virtual ~Entity() = default;

	virtual void loadGFX() = 0;

	vec2 getPos() const;
	Collider& getCollider();
	void addToPos(const vec2& newPos);

	RenderSet getRenderSet() const;

	virtual void update(float dt);

protected:
	Animator& getAnimator();
	AnimationSet*& getAnimationSets();

	void setPos(const vec2& newPos);
	
	int getCurrentASIndex() const;
	void setCurrentASIndex(int nextASIndex);

	RigidBody* getRigidBody() const;

private:

	vec2 pos;
	vec2 velocity;
	//Collider collider;
	Animator animator;
	AnimationSet* animationSets;
	//Current Animation Set Index
	int currentASIndex;

	Collider collider;
	RigidBody* rigidBody;
};

