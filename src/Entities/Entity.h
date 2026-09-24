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
	virtual ~Entity();

	virtual void loadGFX() = 0;

	const vec2& getPos() const;
	Collider& getCollider();
	void addToPos(const vec2& newPos);
	void setPos(const vec2& newPos);

	void setGrounded(bool grounded);

	RenderSet getRenderSet() const;

	void setVelocity(vec2 v) ;
	vec2 getVelocity() const;

	void setVelocityX(float v);
	void setVelocityY(float v);
	void addVelocity(vec2 v);
	virtual void update(float dt);


	vec2 getLastDir() const;
	vec2 getDir() const;
	void setDir(vec2 dir);

	RigidBody* getRigidBody() const;

protected:
	Animator& getAnimator();
	AnimationSet*& getAnimationSets();

	
	void setCollider(vec2 size, vec2 offset);
	void setColliderOffset(vec2 offset);
	int getCurrentASIndex() const;
	void setCurrentASIndex(int nextASIndex);

	
	void setLastDir(vec2 dir);


private:

	vec2 pos;
	vec2 velocity;
	vec2 dir;
	vec2 lastDir;
	//Collider collider;
	Animator animator;
	AnimationSet* animationSets;
	//Current Animation Set Index
	int currentASIndex;

	Collider collider;
	RigidBody* rigidBody;
};

