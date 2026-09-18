#include "precomp.h"
#include "GameScene.h"
#include <surface.h>
#include <Renderer.h>
#include <iostream>
#include <CollisionManager.h>
#include <InputManager.h>

GameScene::GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager) :
	CustomScene(screen, renderer, inputManager), //inheritance
	player(vec2(200,50), getInputManager()), 
	soldier(vec2(300, 50))
	{
		getCamera().setWorldSize(vec2(map.getTiles().x * map.getTileSize(), (map.getTiles().y)* map.getTileSize()));
	}

void GameScene::init() {
	getRenderer().addMapRenderSet(map.getMapRenderSet());
};
void GameScene::exit() {};

void GameScene::update(float dt) {
	getRenderer().clearRenderSets();
	getRenderer().clearColliders();

	player.update(dt);
	soldier.update(dt);
	CollisionManager::resolveMapCollision(player, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
	CollisionManager::resolveMapCollision(soldier, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
	getRenderer().addRenderSet(player.getRenderSet());
	player.getGun().addRenderSets(getRenderer());
	//getRenderer().addRenderSet(player.getGunRenderSet(), player.getGunBullets());

	getRenderer().addCollider(player.getCollider());
	getRenderer().addCollider(soldier.getCollider());
	getCamera().follow(player.getPos());

};


void GameScene::display(float dt) {

	//player.display(dt, screen); //player which as entity

};
