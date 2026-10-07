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
#include <ParallaxRenderData.h>

GameScene::GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager, AudioManager& audioManager, const Map& map_) :
	CustomScene(screen, renderer, inputManager, audioManager),
	player(vec2(30, 80), getInputManager()),
	loseCondition(false),
	winCondition(false),
	justWin(false),
	secondsLeft(9),
	elapsedLoseTime(0.f),
	spawnedEntities{},
	map(map_),
	parallaxRenderData(
			ResourceID::ID_PARALLAX_BG,
			ResourceIDFrames::IDF_PARALLAX_BG,
			0.2f,
			vec2(0,-30)
		),
	waterfall(RenderData
				(AnimationSet(
					1,
					AnimationLayer(
						ResourceID::ID_WATERFALL,
						ResourceIDFrames::IDF_WATERFALL,
						10,
						vec2(0, 0),
						vec2(0, 0)
					)
				),
				vec2(3337,3.5f))
			),
	waterfallBottom(RenderData
				(AnimationSet(
					1,
					AnimationLayer(
						ResourceID::ID_WATERFALL_BOTTOM,
						ResourceIDFrames::IDF_WATERFALL_BOTTOM,
						10,
						vec2(0, 0),
						vec2(0, 0)
					)
				),
				vec2(3318, 3.5))
	)
	{
		getCamera().setWorldSize(vec2(map.getTiles().x * map.getTileSize(), (map.getTiles().y)* map.getTileSize()));	
	}

GameScene::~GameScene() {
	for (int i = 0; i < MAXENTITIES; i++) {
		freeEntity(i);
	}
}

void GameScene::init() {
	player.init(vec2(3250,80));

	//* Initialize camera to game scene settings
	getCamera().init(vec2(0.f, 10.f * map.getTileSize()));
	getCamera().enableCamera(true);
	
	// Add renders
	{
		getRenderer().addMapRenderData(map.getMapRenderData());
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

		getRenderer().addParallaxRenderData(parallaxRenderData);
	}
	
	setChangeScene(false);
	setNextScene(TypeScene::GAME_OVER);

	anim.setAnimation(&waterfall.animationSet);
	anim2.setAnimation(&waterfallBottom.animationSet);

	//TODO: map init to reset spawners timer since they remain in memory
};

void GameScene::exit() {};

// TODO: add proper audio to the game
void GameScene::update(float dt) {
	getRenderer().clearRenderDatas();
	getRenderer().clearColliders();
	getRenderer().clearTexts();

	anim.playAnimation(dt);
	anim2.playAnimation(dt);

	// TODO: ADD layers to the renderData
	getRenderer().addRenderData(waterfall);


	player.update(dt);
	CollisionManager::resolveMapCollision(player, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));

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

		Collider c = player.getCollider();
		c.offset.x += player.getLastDir().x * c.size.x;
		player.setEntityInFront(
			CollisionManager::checkCollision(c,e->getCollider()) ||
			CollisionManager::checkCollision(player.getCollider(), e->getCollider())
		);

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
			enemy->addRenderDatas(getRenderer());

			for (int j = 0; j < enemy->getMaxGranades(); j++) {
				Granade* g = enemy->getGranade(j);
				if (!g) continue;
				
				if (getCamera().isOutOfView(g->getPos())) {
					g->explode();
				}
				
				if (g->hasToBeFreed()) {
					enemy->freeGranade(j);
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
				if (player.isShooting() && !pow->isReleased()) {
					pow->setReleased(true);
					player.addPowSaved();
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
				CollisionManager::resolveCollisionAOverB(player, lootDrop->getCollider());
				lootDrop->applyEffect(player);
			}
		}

		getRenderer().addRenderData(e->getRenderData());
		getRenderer().addCollider(e->getCollider());


		
	}



	
	for (int i = 0; i < player.getGun().getMaxBullets(); i++) {
		Bullet* b = player.getGun().getBullet(i);
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
			b->explodeMap();
		}
		for (Entity* e : this->spawnedEntities) {
			if (!e) continue;
			if (e->getEntityType() == EntityType::ET_REBELSOLDIER){

				RebelSoldier* enemy = static_cast<RebelSoldier*>(e);
				if (!enemy->getAlive()) continue;
				
				if (CollisionManager::checkCollision(b->getCollider(), enemy->getCollider())) {
					b->explode();
					enemy->setAlive(false);
					player.addScore(100);
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

	

	
	getRenderer().addRenderData(player.getRenderData());
	player.getGun().addRenderDatas(getRenderer());
	//getRenderer().addRenderData(player.getGunRenderData(), player.getGunBullets());
	getRenderer().addRenderData(waterfallBottom);

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

		}else {
			if(winCondition){
				char savedText[4];
				snprintf(savedText, sizeof(savedText), "%d", player.getPowSaved());

				if(justWin){
					getRenderer().addSpriteSet(SpriteSet(
						ResourceID::ID_POW_BYE,
						ResourceIDFrames::IDF_POW_BYE,
						vec2(40, 60),
						10
					));
					justWin = false;
				}

				// TODO: Dark background
				getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "RECAPTURED PRISONER", vec2(45, 40), 1.f });
				getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, "P1", vec2(65, 50), 1.f });
				getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, savedText, vec2(80, 82), 1.f });
				getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "x1000", vec2(105, 90), 1.f });
				getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, "11000", vec2(60, 110), 1.f });
				getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "MG. Carothers", vec2(30, 145), 1.f });
				getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "PLEASE WAIT", vec2(180, 10),1.2f });
				
			}
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
	justWin = player.getPos().x > 1000 && !winCondition;
	winCondition = player.getPos().x > 1000;
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