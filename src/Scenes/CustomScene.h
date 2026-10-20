#pragma once
#include <Renderer.h>
#include <InputManager.h>
#include <AudioManager.h>
#include <ResourceManager.h>
#include <Camera.h>

class Tmpl8::Surface;
enum TypeScene : int;

class CustomScene
{
public:
	CustomScene(Surface* screen, Renderer& renderer_, InputManager& inputManager_, AudioManager& audioManager_, ResourceManager& resourceManager_);
	virtual ~CustomScene() {};
	virtual void init() = 0;
	virtual void exit() = 0;

	vec2 getCameraPos() const;
	virtual void update(float dt) = 0;

	TypeScene getNextScene() const;
	bool sceneHasToChange() const;

protected:
	Renderer& getRenderer() const;
	ResourceManager& getResourceManager() const;
	InputManager& getInputManager() const;
	AudioManager& getAudioManager() const;
	Camera& getCamera();

	void setNextScene(TypeScene nextScene_);
	void setChangeScene(bool changeScene_);

	void setFirstFrame(bool firstFrame_);
	bool isFirstFrame() const;
private:
	Renderer& renderer;
	InputManager& inputManager;
	AudioManager& audioManager;
	ResourceManager& resourceManager;
	Camera camera;

	bool changeScene;
	TypeScene nextScene;	
	bool firstFrame;

};

