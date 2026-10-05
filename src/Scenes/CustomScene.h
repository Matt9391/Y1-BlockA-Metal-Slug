#pragma once
#include <Renderer.h>
#include <InputManager.h>
#include <Camera.h>

class Tmpl8::Surface;
enum TypeScene : int;

class CustomScene
{
public:
	CustomScene(Surface* screen, Renderer& renderer, InputManager& inputManager);
	virtual ~CustomScene() {};
	virtual void init() = 0;
	virtual void exit() = 0;

	vec2 getCameraPos() const;
	virtual void update(float dt) = 0;

	TypeScene getNextScene() const;
	bool sceneHasToChange() const;

protected:
	Renderer& getRenderer() const;
	InputManager& getInputManager() const;
	Camera& getCamera();

	void setNextScene(TypeScene nextScene_);
	void setChangeScene(bool changeScene_);

private:
	Renderer& renderer;
	InputManager& inputManager;
	Camera camera;

	bool changeScene;
	TypeScene nextScene;

};

