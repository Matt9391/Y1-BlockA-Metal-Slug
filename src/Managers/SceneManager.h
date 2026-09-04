#pragma once
#include <CustomScene.h>

enum TypeScene;
class Tmpl8::Surface;

class SceneManager
{
public:
	SceneManager();

	void init(Surface* screen, TypeScene firstScene);

	CustomScene& getCurrentScene();
	
	void changeScene(TypeScene nextScene);


private:
	CustomScene* currentScene;
	CustomScene* menuScene;
	CustomScene* gameScene;

};

