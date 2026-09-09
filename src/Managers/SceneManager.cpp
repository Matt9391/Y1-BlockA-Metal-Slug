#include "precomp.h"
#include "SceneManager.h"
#include "TypeScene.h"
#include <GameScene.h>
#include <Renderer.h>


SceneManager::SceneManager() :
	currentScene(nullptr),
	menuScene(nullptr),
	gameScene(nullptr)
	{
	}

SceneManager::~SceneManager() {
	delete currentScene;
	delete menuScene;
	delete gameScene;
}

void SceneManager::init(Surface* screen, Renderer& renderer, TypeScene firstScene) {
	gameScene = new GameScene(screen, renderer);
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

	currentScene->init();
}

