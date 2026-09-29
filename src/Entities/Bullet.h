#pragma once
#include <Entity.h>

class Bullet : public Entity {

public:

	Bullet(vec2 pos, bool needsRigidBody, vec2 dir);
	~Bullet() override;

	void loadGFX() override;
	
	void update(float dt) override;

	void explode();
	bool getDisabled() const;


private:
	bool ableMovement;
	bool isDisabled;
};