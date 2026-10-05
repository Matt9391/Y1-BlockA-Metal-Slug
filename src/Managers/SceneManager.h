#pragma once
#include <CustomScene.h>

enum TypeScene : int;
class Tmpl8::Surface;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init(Surface* screen, Renderer& renderer, InputManager& inputManager, ResourceManager& resourceManager, TypeScene firstScene);

	CustomScene& getCurrentScene() const;
	
	void changeScene(TypeScene nextScene,Surface* screen, Renderer& renderer, InputManager& inputManager, ResourceManager& resourceManager);


private:
	CustomScene* currentScene;
};

