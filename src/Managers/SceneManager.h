#pragma once
#include <CustomScene.h>

enum TypeScene;
class Tmpl8::Surface;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init(Surface* screen, Renderer& renderer, TypeScene firstScene);

	CustomScene& getCurrentScene() const;
	
	void changeScene(TypeScene nextScene);


private:
	CustomScene* currentScene;
	CustomScene* menuScene;
	CustomScene* gameScene;
};

