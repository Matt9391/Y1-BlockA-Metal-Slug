#pragma once
#include <Renderer.h>
#include <InputManager.h>
#include <Camera.h>

class Tmpl8::Surface;

class CustomScene
{
public:
	CustomScene(Surface* screen, Renderer& renderer, InputManager& inputManager);

	virtual void init() = 0;
	virtual void exit() = 0;

	vec2 getCameraPos() const;
	virtual void update(float dt) = 0;
	virtual void display(float dt) = 0;

protected:
	Surface* getScreen() const;
	Renderer& getRenderer() const;
	InputManager& getInputManager() const;
	Camera& getCamera();
private:
	Surface* screen;
	Renderer& renderer;
	InputManager& inputManager;
	Camera camera;

};

