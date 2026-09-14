#include "precomp.h"
#include "GameScene.h"
#include <surface.h>
#include <Renderer.h>
#include <iostream>
#include <CollisionManager.h>

GameScene::GameScene(Surface* screen, Renderer& renderer) :
	CustomScene(screen, renderer), //inheritance
	player(vec2(200,100)) //my own helper class
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
	renderer.addMapRenderSet(map.getMapRenderSet());
	camera.follow(player.getPos());

};


void GameScene::display(float dt) {

	//player.display(dt, screen); //player which as entity

};
