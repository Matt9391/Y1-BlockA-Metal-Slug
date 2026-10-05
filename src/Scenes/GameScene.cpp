#include "precomp.h"
#include "GameScene.h"
#include <surface.h>
#include <Renderer.h>
#include <iostream>
#include <CollisionManager.h>
#include <InputManager.h>
#include <ResourceIDFrames.h>
#include <Bullet.h>
#include <TypeScene.h>
#include <Pow.h>
#include <Enemies/RebelSoldier.h>
#include <LootDrop.h>
#include <LootDrops/PowerUp.h>

GameScene::GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager) :
	CustomScene(screen, renderer, inputManager),
	player(vec2(30, 80), getInputManager()),
	loseCondition(false),
	secondsLeft(9),
	elapsedLoseTime(0.f),
	spawnedEntities{}
	{
		getCamera().setWorldSize(vec2(map.getTiles().x * map.getTileSize(), (map.getTiles().y)* map.getTileSize()));	
	}

GameScene::~GameScene() {
	for (int i = 0; i < MAXENTITIES; i++) {
		freeEntity(i);
	}
}

void GameScene::init() {
	//* Initialize camera to game scene settings
	getCamera().init(vec2(0, 10 * map.getTileSize()));
	getCamera().enableCamera(true);
	// Add renders
	{
		getRenderer().addMapRenderSet(map.getMapRenderSet());
		getRenderer().clearSpriteSets();
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

	}
	
	setChangeScene(false);
	setNextScene(TypeScene::GAME_OVER);
};

void GameScene::exit() {};

void GameScene::update(float dt) {
	getRenderer().clearRenderSets();
	getRenderer().clearColliders();
	getRenderer().clearTexts();

	player.update(dt);

	if (player.getEnabled()) {

		for (int i = 0; i < map.getSpawnersLayers(); i++) {
			Spawner** layerSpawners = map.getSpawners(i);
			for (int j = 0; j < map.getSpawnersCount()[i]; j++) {
				Spawner& spawner = *layerSpawners[j];

				spawner.setDistToPlayer(player.getPos().x - spawner.getPos().x);
				spawner.update(dt);

				Entity* newEntity = spawner.createEntity();
				addNewEntity(newEntity);
			}
		}
	}


	for (int i = 0; i < MAXENTITIES; i++) {
		Entity* e = this->spawnedEntities[i];
		if (!e) continue;
		e->update(dt);

		if(e->hasToBeFreed()){
			freeEntity(i);
			continue;
		}

		CollisionManager::resolveMapCollision(*e, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
		
		if (e->getEntityType() == EntityType::ET_REBELSOLDIER) {

			RebelSoldier* enemy = static_cast<RebelSoldier*>(e); //static vs dynamic ?
				
			enemy->loadSensors(
				player.getPos() + player.getCollider().size / 2.f,
				CollisionManager::checkMapCollision(
					enemy->getCollider(),
					map.getLayer(MapLayerNames::MLN_COLLISION_LAYER),
					0
				)
			);

			if (enemy->getAttacking() && CollisionManager::checkCollision(player.getCollider(), enemy->getCollider())) {
				player.takeHit();
			}
			enemy->addRenderSets(getRenderer());

			for (int i = 0; i < enemy->getMaxGranades(); i++) {
				Granade* g = enemy->getGranade(i);
				if (!g) continue;
				
				if (getCamera().isOutOfView(g->getPos())) {
					g->explode();
				}
				
				if (g->hasToBeFreed()) {
					enemy->freeGranade(i);
					continue;
				}
				if(g->getDisabled()) continue;

				if (CollisionManager::checkMapCollision(g->getCollider(), map.getLayer(MapLayerNames::MLN_COLLISION_LAYER), -1)) {
					g->explode();
				}

				if (CollisionManager::checkCollision(g->getCollider(), player.getCollider())) {
					g->explode();
					player.takeHit();
				}
			}
		}
		else if (e->getEntityType() == EntityType::ET_POW) {
			Pow* pow = static_cast<Pow*>(e);
			if (CollisionManager::checkCollision(player.getCollider(), pow->getCollider())) {
				if (player.isShooting()) {
					pow->setReleased(true);
				}
				pow->setIntersectingPlayer(true);
			}
			else {
				pow->setIntersectingPlayer(false);
			}

			if (getCamera().isOutOfView(pow->getPos())) {
				if (pow->isReleased()) {
					pow->setPowFree(true);
				}
			}
			// TODO: think of a better solution for checking entity type of lootdrop
		}else if(e->getEntityType() == EntityType::ET_LOOTDROP ||
				e->getEntityType() == EntityType::ET_POWERUP){
			LootDrop* lootDrop = static_cast<LootDrop*>(e);

			// TODO: Add player colllision resolution on lootdrop, it can walk over it
			if (CollisionManager::checkCollision(player.getCollider(), lootDrop->getCollider())) {
				lootDrop->applyEffect(player);
			}
		}

		getRenderer().addRenderSet(e->getRenderSet());
		getRenderer().addCollider(e->getCollider());


		
	}



	Collider c = player.getCollider();
	c.offset.x += player.getLastDir().x * c.size.x;
	//player.setEnemyInFront(
	//	CollisionManager::checkCollision(c,soldier.getCollider()) ||
	//	CollisionManager::checkCollision(player.getCollider(), soldier.getCollider())
	//);

	CollisionManager::resolveMapCollision(player, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
	
	for (int i = 0; i < player.getGun().getMaxBullets(); i++) {
		Bullet* b = player.getGun().getBullet(i);
		bool free = false;
		if (!b) continue;

		if (b->hasToBeFreed()) {
			player.getGun().freeBullet(i);
			continue;
		}
		if (b->getDisabled()) continue;

		if (getCamera().isOutOfView(b->getPos())) {
			b->explode();
		}
		
		if (CollisionManager::checkMapCollision(b->getCollider(), map.getLayer(MapLayerNames::MLN_COLLISION_LAYER), -1)) {
			b->explode();
		}
		for (Entity* e : this->spawnedEntities) {
			if (!e) continue;
			if (e->getEntityType() == EntityType::ET_REBELSOLDIER){

				RebelSoldier* enemy = static_cast<RebelSoldier*>(e);
				if (!enemy->getAlive()) continue;
				
				if (CollisionManager::checkCollision(b->getCollider(), enemy->getCollider())) {
					b->explode();
					enemy->setAlive(false);
				}
				
			}else if(e->getEntityType() == EntityType::ET_POWERUP){
				PowerUp* powerUp = static_cast<PowerUp*>(e);
				
				if (CollisionManager::checkCollision(b->getCollider(), powerUp->getCollider())) {
					b->explode();
					powerUp->setState(PowerUpState::PUS_REVEALED);
				}
			}
		}
	}

	

	
	getRenderer().addRenderSet(player.getRenderSet());
	player.getGun().addRenderSets(getRenderer());
	//getRenderer().addRenderSet(player.getGunRenderSet(), player.getGunBullets());

	getRenderer().addCollider(player.getCollider());
	//Collider c = player.getCollider();
	//c.offset.x += player.getLastDir().x * c.size.x;
	//getRenderer().addCollider(c);
	getCamera().follow(player.getPos());

	//HUD
	{

		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "LEVEL-4", vec2(150, 215),1.f});
		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "CREDIT 01", vec2(220, 215),1.f});

		if (loseCondition) {
			elapsedLoseTime += dt;

			if (elapsedLoseTime > 1000) {
				elapsedLoseTime = 0.f;
				secondsLeft--;
				secondsLeft = secondsLeft < 0 ? 0 : secondsLeft;
			}

			if (secondsLeft == 0) {
				setChangeScene(true);
			}

			char timeLeft[50];
			snprintf(timeLeft, sizeof(timeLeft), "%d", secondsLeft);
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, "CONTINUE?", vec2(80, 80),1.f });
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, timeLeft, vec2(130, 100),2.f });
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "CONTINUE ", vec2(10, 10),1.f });
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, timeLeft, vec2(90, 10),1.f });
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "PUSH START", vec2(180, 10),1.f });

			if(getInputManager().isKeyPressed(' ')) {
				player.fullRevive();	
			}

		}
		else {
			char livesText[50];
			snprintf(livesText, sizeof(livesText), "1UP=%d", player.getLives());
			char scoreText[50];
			snprintf(scoreText, sizeof(scoreText), "%d", player.getScore());
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, scoreText, vec2(38, 2),0.5f });
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE, livesText, vec2(10, 20),0.8f });
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE_S, "200", vec2(95, 10),1.f });
			getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE_S, "10", vec2(130, 10),1.f });
		}

	}

	loseCondition = player.getLives() <= -1;
};


void GameScene::display(float dt) {

	//player.display(dt, screen); //player which as entity

};

void GameScene::addNewEntity(Entity* e) {
	if (e == nullptr) return;

	int spawnIndex = -1;

	for (int i = 0; i < MAXENTITIES; i++) {
		Entity* se = spawnedEntities[i]; //se - spawned entities
		if (se == nullptr) {
			spawnIndex = i;
			break;
		}
	}

	if (spawnIndex != -1) {
		spawnedEntities[spawnIndex] = e;
	}
	else {
		throw runtime_error("Max entities reached");
	}
}

// TODO: shift back entities to minimize looping, also in the other arrays 	
void GameScene::freeEntity(int index) {
	if (spawnedEntities[index]) {
		delete spawnedEntities[index];
		spawnedEntities[index] = nullptr;
	}
}