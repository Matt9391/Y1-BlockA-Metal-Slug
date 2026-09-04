#pragma once

class Tmpl8::Surface;

class CustomScene
{
public:
	CustomScene(Surface* screen);

	virtual void init() = 0;
	virtual void exit() = 0;

	virtual void update(float dt) = 0;
	virtual void display() = 0;

protected:
	Surface* screen;
};

