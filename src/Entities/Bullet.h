#pragma once
#include <Entity.h>

enum BulletType : int;

class Bullet : public Entity {

public:

	Bullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	virtual ~Bullet() {};


	virtual	void explode() = 0;
	virtual void explodeMap() = 0;
	
	bool getDisabled() const;
protected:

	void setDisabled(bool isDisabled_);
	void setAbleMovement(bool ableMovement_);

	bool getAbleMovement() const;

private:
	bool ableMovement;
	bool isDisabled;
	BulletType bulletType;
};