#include "precomp.h"
#include "SceneManager.h"
#include "TypeScene.h"
#include <GameScene.h>
#include <MenuScene.h>
#include <GameOverScene.h>
#include <Renderer.h>
#include <InputManager.h>


SceneManager::SceneManager() :
	currentScene(nullptr)
	{
	}

SceneManager::~SceneManager() {
	delete currentScene;
}

void SceneManager::init(Surface* screen, Renderer& renderer, InputManager& inputManager, TypeScene firstScene) {
	// gameScene = new GameScene(screen, renderer, inputManager);
	// menuScene = new MenuScene(screen, renderer, inputManager);
	changeScene(firstScene, screen, renderer, inputManager);
}

CustomScene& SceneManager::getCurrentScene() const{
	return *currentScene;
}


void SceneManager::changeScene(TypeScene nextScene,Surface* screen, Renderer& renderer, InputManager& inputManager) {
	renderer.reset();
	delete currentScene;
	if (nextScene == TypeScene::MENU) {
		currentScene = new MenuScene(screen, renderer, inputManager);
	}
	else if (nextScene == TypeScene::GAME_OVER) {
		currentScene = new GameOverScene(screen, renderer, inputManager);
	}else{
		currentScene = new GameScene(screen, renderer, inputManager);
	}

	currentScene->init();
}

