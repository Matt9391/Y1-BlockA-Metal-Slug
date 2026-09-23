#pragma once
#include <Entity.h>
#include <PowState.h>


class Pow : public Entity {
public:
	Pow(vec2 pos);
	~Pow() override;

	void loadGFX() override;

	void update(float dt) override;

	bool isReleased() const;
	void setReleased(bool released);

	bool isAnimationEnded();
	
	bool isIntersectingPlayer() const;
	void setIntersectingPlayer(bool intersect);

private:
	PowStates::PowState* state;
	bool released;
	bool intersectingPlayer;
};