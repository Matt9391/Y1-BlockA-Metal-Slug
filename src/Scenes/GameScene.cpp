#include "precomp.h"
#include "GameScene.h"
#include <surface.h>

GameScene::GameScene(Surface* screen) :
	CustomScene(screen),
	player(vec2(100,100))
	{

	}

void GameScene::init() {};
void GameScene::exit() {};

void GameScene::update(float dt) {};
void GameScene::display() {

	player.display(screen);

};
