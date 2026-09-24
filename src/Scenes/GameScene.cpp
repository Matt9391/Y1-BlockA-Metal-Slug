#include "precomp.h"
#include "GameScene.h"
#include <surface.h>
#include <Renderer.h>
#include <iostream>
#include <CollisionManager.h>
#include <InputManager.h>
#include <Bullet.h>

GameScene::GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager) :
	CustomScene(screen, renderer, inputManager), 
	player(vec2(200, 50), getInputManager()),
	soldier(vec2(300, 50)),
	pow(vec2(900, 50))
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
	getRenderer().clearTexts();

	player.update(dt);
	soldier.loadSensors(
		player.getPos(),
		CollisionManager::checkMapCollision(soldier.getCollider(), map.getLayer(MapLayerNames::MLN_COLLISION_LAYER), 0)
	);
	soldier.update(dt);
	if (CollisionManager::checkCollision(player.getCollider(), pow.getCollider())) {
		if (player.isShooting()) {
			pow.setReleased(true);
		}
		pow.setIntersectingPlayer(true);
	}
	else {
		pow.setIntersectingPlayer(false);
	}

	pow.update(dt);

	CollisionManager::resolveMapCollision(player, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
	CollisionManager::resolveMapCollision(soldier, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
	CollisionManager::resolveMapCollision(pow, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
	
	for (int i = 0; i < player.getGun().getMaxBullets(); i++) {
		Bullet* b = player.getGun().getBullet(i);
		bool free = false;
		//if (b) std::cout << (*b).getRigidBody();
		if (b && CollisionManager::resolveMapCollision(*b, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER))) {
			free = true;
		}

		if (b && CollisionManager::checkCollision(b->getCollider(), soldier.getCollider())) {
			free = true;
		}
		if(free) player.getGun().freeBullet(i);
	}

	if (soldier.getAttacking() && CollisionManager::checkCollision(player.getCollider(), soldier.getCollider())) {
		printf("HIT\n");
	}

	for (int i = 0; i < soldier.getMaxGranades(); i++) {
		Granade* g = soldier.getGranade(i);
		bool free = false;
		//if (b) std::cout << (*b).getRigidBody();
		if (g && CollisionManager::resolveMapCollision(*g, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER))) {
			free = true;
		}

		if (g && CollisionManager::checkCollision(g->getCollider(), player.getCollider())) {
			free = true;
		}
		if (free) soldier.freeGranade(i);
	}

	getRenderer().addRenderSet(player.getRenderSet());
	getRenderer().addRenderSet(soldier.getRenderSet());
	getRenderer().addRenderSet(pow.getRenderSet());
	player.getGun().addRenderSets(getRenderer());
	soldier.addRenderSets(getRenderer());
	//getRenderer().addRenderSet(player.getGunRenderSet(), player.getGunBullets());

	getRenderer().addCollider(player.getCollider());
	getRenderer().addCollider(soldier.getCollider());
	getRenderer().addCollider(pow.getCollider());
	getCamera().follow(player.getPos());

	//getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE, "bella bro\nahah", vec2(100, 100),1});
	//getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, "ciao a te", vec2(250, 100),0.5f });

};


void GameScene::display(float dt) {

	//player.display(dt, screen); //player which as entity

};
