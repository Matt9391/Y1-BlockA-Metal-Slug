#include "precomp.h"
#include "GameScene.h"
#include <surface.h>
#include <Renderer.h>
#include <iostream>
#include <CollisionManager.h>
#include <InputManager.h>
#include <ResourceIDFrames.h>
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
	getRenderer().addSpriteSet(SpriteSet(
		ResourceID::ID_FUEL_BAR,
		ResourceIDFrames::IDF_FUEL_BAR,
		vec2(10, 12)
	));

	getRenderer().addSpriteSet(SpriteSet(
		ResourceID::ID_AMMOS,
		ResourceIDFrames::IDF_AMMOS,
		vec2(90, 2)
	)); 
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

	Collider c = player.getCollider();
	c.offset.x += player.getLastDir().x * c.size.x;
	player.setEnemyInFront(
		CollisionManager::checkCollision(c,soldier.getCollider()) ||
		CollisionManager::checkCollision(player.getCollider(), soldier.getCollider())
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
	//Collider c = player.getCollider();
	//c.offset.x += player.getLastDir().x * c.size.x;
	getRenderer().addCollider(c);
	getCamera().follow(player.getPos());

	//HUD
	{
		char livesText[50];
		snprintf(livesText, sizeof(livesText), "1UP=%d", player.getLives());
		char scoreText[50];
		snprintf(scoreText, sizeof(scoreText), "%d", player.getScore());

		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, scoreText, vec2(38, 2),0.5f });
		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE, livesText, vec2(10, 20),0.8f });
		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE_S, "200", vec2(95, 10),1.f});
		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE_S, "10", vec2(130, 10),1.f});
		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "LEVEL-4", vec2(150, 215),1.f});
		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "CREDIT 01", vec2(220, 215),1.f});

		

	}

};


void GameScene::display(float dt) {

	//player.display(dt, screen); //player which as entity

};
