#include "precomp.h"
#include "GameScene.h"
#include <surface.h>
#include <Renderer.h>
#include <iostream>
#include <CollisionManager.h>
#include <InputManager.h>

GameScene::GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager) :
	CustomScene(screen, renderer, inputManager), //inheritance
	player(vec2(200,50), inputManager) //my own helper class
	{
		camera.setWorldSize(map.getTiles() * map.getTileSize());
	}

void GameScene::init() {
	player.loadGFX();
	renderer.addMapRenderSet(map.getMapRenderSet());
};
void GameScene::exit() {};

void GameScene::update(float dt) {
	player.update(dt);
	renderer.clearRenderSets();
    RenderSet rs = player.getRenderSet();
	renderer.addRenderSet(rs);
	CollisionManager::resolveMapCollision(player, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
	camera.follow(player.getPos());

};


void GameScene::display(float dt) {

	//player.display(dt, screen); //player which as entity

};
