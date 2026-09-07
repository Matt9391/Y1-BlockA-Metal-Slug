#include "precomp.h"
#include "GameScene.h"
#include <surface.h>
#include <ResourceManager.h>

GameScene::GameScene(Surface* screen, ResourceManager& resourceManager) :
	CustomScene(screen, resourceManager), //inheritance
	player(vec2(100,100)) //my own helper class
	{

	}

void GameScene::init() {
	player.loadGFX(resourceManager);

};
void GameScene::exit() {};

void GameScene::update(float dt) {};
void GameScene::display(float dt) {

	player.display(dt, screen); //player which as entity

};
