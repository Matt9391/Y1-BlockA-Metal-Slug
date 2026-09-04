#include "precomp.h"
#include "SceneManager.h"
#include "TypeScene.h"
#include <GameScene.h>


SceneManager::SceneManager() :
	currentScene(nullptr),
	menuScene(nullptr),
	gameScene(nullptr)
	{
	}

void SceneManager::init(Surface* screen, TypeScene firstScene) {
	gameScene = new GameScene(screen);
	changeScene(firstScene);
}

CustomScene& SceneManager::getCurrentScene() {
	return *currentScene;
}


void SceneManager::changeScene(TypeScene nextScene) {
	if (nextScene == TypeScene::MENU) {
		currentScene = menuScene;
	}
	else {
		currentScene = gameScene;
	}
}

