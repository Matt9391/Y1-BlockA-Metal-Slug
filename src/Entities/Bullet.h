#pragma once
#include <Entity.h>

enum BulletType : int;

class Bullet : public Entity {

public:

	Bullet(vec2 pos, bool needsRigidBody, vec2 dir, BulletType bulletType, float bulletSpeed);
	~Bullet() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	bool getDisabled() const;


private:
	bool ableMovement;
	bool isDisabled;
	BulletType bulletType;
};