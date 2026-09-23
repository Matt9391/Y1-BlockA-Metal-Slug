#pragma once
#include <Entity.h>

class Granade : public Entity {
public:
	Granade(vec2 pos, bool needsRigidBody, vec2 dir);
	~Granade() override;

	void loadGFX() override;

	void update(float dt) override;
private:
	float arcWidth;
	vec2 startPos;
	float duration;
	float peakHeight;
	float elapsedTime;
};