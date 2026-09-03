#include "precomp.h"
#include "SceneManager.h"
#include "TypeScene.h"

SceneManager::SceneManager(TypeScene firstScene) :
	currentScene(nullptr),
	menuScene(nullptr),
	gameScene(nullptr)
	{
		changeScene(firstScene);
	}

void SceneManager::changeScene(TypeScene nextScene) {
	if (nextScene == TypeScene::MENU) {
		currentScene = menuScene;
	}
	else {
		currentScene = gameScene;
	}
}