#pragma once
#include <Entity.h>

class Bullet : public Entity {

public:

	Bullet(vec2 pos, bool needsRigidBody);

	void loadGFX() override;
	
	void update(float dt) override;

private:

};