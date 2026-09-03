#pragma once

class Scene;
enum TypeScene;

class SceneManager
{
public:
	SceneManager(TypeScene firstScene);

	Scene& getCurrentScene();
	
	void changeScene(TypeScene nextScene);


private:
	Scene* currentScene;
	Scene* menuScene;
	Scene* gameScene;

};

