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
#include <Enemies/Helicopter.h>
#include <LootDrop.h>
#include <LootDrops/PowerUp.h>
#include <ParallaxRenderData.h>
#include <Enemies/Boss.h>
#include <GunPresets.h>
#include <Tank.h>

//TODO: add player change gun after tot shoots
GameScene::GameScene(Surface* screen, Renderer& renderer, InputManager& inputManager, AudioManager& audioManager, ResourceManager& resourceManager, const Map& map_) :
	CustomScene(screen, renderer, inputManager, audioManager, resourceManager),
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
				vec2(3337,3.5f), 0)
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
	),
	nTilesLimit1Camera(231),
	nTilesLimit2Camera(static_cast<int>(map.getTiles().x))
	{
	}

GameScene::~GameScene() {
	for (int i = 0; i < MAXENTITIES; i++) {
		freeEntity(i);
	}
}

void GameScene::init() {
	player.init(vec2(30,80));

	getRenderer().setDarkOverlay(false);
	

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

		// DONE: make it a variable limit1
		getCamera().setWorldSize(vec2(static_cast<float>(nTilesLimit1Camera * map.getTileSize()), 
									  static_cast<float>(map.getTiles().y * map.getTileSize()))
		);
	}
	
	setChangeScene(false);
	setNextScene(TypeScene::GAME_OVER);

	anim.setAnimation(&waterfall.animationSet);
	anim2.setAnimation(&waterfallBottom.animationSet);

	//DONE: map init to reset spawners timer since they remain in memory
	for (int i = 0; i < map.getSpawnersLayers(); i++) {
			Spawner** layerSpawners = map.getSpawners(i);
			for (int j = 0; j < map.getSpawnersCount()[i]; j++) {
				Spawner& spawner = *layerSpawners[j];

				spawner.init();
			}
		}
	
	tankRef = new Tank(vec2(700,80), getInputManager());
	addNewEntity(tankRef);
	addNewEntity(new Boss(vec2(3769 + 265, -60 + 100)));
};

void GameScene::exit() {};

// TODO: add proper audio to the game
void GameScene::update(float dt) {
	getRenderer().clearRenderDatas();
	getRenderer().clearColliders();
	getRenderer().clearRadiusData();
	getRenderer().clearTexts();

	anim.playAnimation(dt);
	anim2.playAnimation(dt);

	player.update(dt);
	if(player.getGun().getBulletShot() > 15){
		player.setGunData(GunPresets::getGun(GunType::PISTOL));
	}
	
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


	
	Collider playerColliderInFront = player.getCollider();
	playerColliderInFront.offset.x += player.getLastDir().x * playerColliderInFront.size.x;
	bool entityInFront = false;
	for (int i = 0; i < MAXENTITIES; i++) {
		Entity* e = this->spawnedEntities[i];
		if (!e) continue;
		e->update(dt);

		if(e->hasToBeFreed()){
			freeEntity(i);
			continue;
		}
		
		if (!entityInFront && 
			CollisionManager::checkCollision(playerColliderInFront,e->getCollider(), getResourceManager()) ||
			CollisionManager::checkCollision(player.getCollider(), e->getCollider(), getResourceManager())){
			entityInFront = true;
		}

		CollisionManager::resolveMapCollision(*e, map.getLayer(MapLayerNames::MLN_COLLISION_LAYER));
		
		switch (e->getEntityType()) {
			case EntityType::ET_REBELSOLDIER:
				handleRebelSoldier(static_cast<RebelSoldier*>(e)); 
				break;

			case EntityType::ET_POW:
				handlePow(static_cast<Pow*>(e));
				break;

			case EntityType::ET_LOOTDROP:
			case EntityType::ET_POWERUP:
				handleLootDrop(e, playerColliderInFront);
				break;

			case EntityType::ET_HELICOPTER:
				handleHelicopter(static_cast<Helicopter*>(e)); 
				break;

			case EntityType::ET_BOSS:
				handleBoss(static_cast<Boss*>(e));
				break;

			case EntityType::ET_TANK:
				handleTank(static_cast<Tank*>(e));
				break;

			default:
				break;
		}

		getRenderer().addRenderData(e->getRenderData());
		getRenderer().addCollider(e->getCollider());
		getRenderer().addRadiusData(e->getRadiusData());
			
	}
	
	player.setEntityInFront(entityInFront);

	// TODO: add entity manager
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

		resolveBulletVsEntities(b);
	}

	if(tankRef != nullptr){
		for (int i = 0; i < tankRef->getMaxBullets(); i++) {
			Bullet* b = tankRef->getBullet(i);
			if (!b) continue;

			if (b->hasToBeFreed()) {
				tankRef->freeBullet(i);
				continue;
			}
			if (b->getDisabled()) continue;

			if (getCamera().isOutOfView(b->getPos())) {
				b->explode();
			}

			if (CollisionManager::checkMapCollision(b->getCollider(), map.getLayer(MapLayerNames::MLN_COLLISION_LAYER), -1)) {
				b->explodeMap();
			}
			
			// TODO: add collision on correct bullet  
			resolveBulletVsEntities(b);
		}
	}
	
	if(!player.getInTank())
		getRenderer().addRenderData(player.getRenderData());
		player.getGun().addRenderDatas(getRenderer());
	if(tankRef){
		tankRef->addRenderDatas(getRenderer());
	}
	//getRenderer().addRenderData(player.getGunRenderData(), player.getGunBullets());
	// DONE: ADD layers to the renderData
	getRenderer().addRenderData(waterfall);
	getRenderer().addRenderData(waterfallBottom);
	
	getRenderer().addCollider(player.getCollider());
	getRenderer().addRadiusData(player.getRadiusData());
	//Collider c = player.getCollider();
	//c.offset.x += player.getLastDir().x * c.size.x;
	//getRenderer().addCollider(c);
	getCamera().follow(player.getPos(), dt);

	renderHUD(dt);

	loseCondition = player.getLives() <= -1;
};


// ---------------------------------------------------------------------------
// HUD
// ---------------------------------------------------------------------------
void GameScene::renderHUD(float dt) {

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
				getRenderer().setDarkOverlay(true);
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


// ---------------------------------------------------------------------------
// Shared helpers
// ---------------------------------------------------------------------------

// A bullet fired by the player or the tank, checked against every entity type.
void GameScene::resolveBulletVsEntities(Bullet* b) {
	for (Entity* e : this->spawnedEntities) {
		if (!e) continue;
		if (e->getEntityType() == EntityType::ET_REBELSOLDIER){

			RebelSoldier* enemy = static_cast<RebelSoldier*>(e);
			if (!enemy->getAlive()) continue;
			
			if (CollisionManager::checkCollision(b->getCollider(), enemy->getCollider(), getResourceManager(),1)) {
				b->explode();
				enemy->setAlive(false);
				player.addScore(100);
			}
			
		}else if (e->getEntityType() == EntityType::ET_POW) {
			Pow* pow = static_cast<Pow*>(e);
			if (CollisionManager::checkCollision(b->getCollider(), pow->getCollider(), getResourceManager(),1)) {
				b->explode();
				pow->setReleased(true);
			}
		}else if(e->getEntityType() == EntityType::ET_POWERUP){
			PowerUp* powerUp = static_cast<PowerUp*>(e);
			if(!powerUp) continue;
			if(powerUp->getState() == PowerUpState::PUS_REVEALED) continue;
			if (CollisionManager::checkCollision(b->getCollider(), powerUp->getCollider(), getResourceManager(),1)) {
				b->explode();
				powerUp->setState(PowerUpState::PUS_REVEALED);
			}
		}else if(e->getEntityType() == EntityType::ET_HELICOPTER){
			Helicopter* h = static_cast<Helicopter*>(e); 
			
			if (CollisionManager::checkCollision(b->getCollider(), h->getCollider(), getResourceManager(),1)) {
				b->explode();
				h->takeHit();
				b->setDisabled(true);
				
			}
			
		}
		else if(e->getEntityType() == EntityType::ET_BOSS){
			Boss* bs = static_cast<Boss*>(e); 
			if (!bs->getAlive()) {
				justWin = !winCondition;
				winCondition = true;
			}

			if (CollisionManager::checkCollision(b->getCollider(), bs->getCollider(), getResourceManager(),1)) {
				b->explode();
				bs->takeHit();
				// player.addScore(100);
			}
		}
	}
}

// Hits the tank if the player is riding it, otherwise hits the player.
void GameScene::damagePlayerOrTank() {
	if(player.getInTank()){
		tankRef->takeHit();
	}else{
		player.takeHit();
	}
}

// Feeds an enemy its target position and whether it is touching the map.
void GameScene::loadEnemySensors(Enemy* enemy, vec2 targetPos) {
	enemy->loadSensors(
		targetPos,
		CollisionManager::checkMapCollision(
			enemy->getCollider(),
			map.getLayer(MapLayerNames::MLN_COLLISION_LAYER),
			0
		)
	);
}


// entity-type handlers
void GameScene::handleRebelSoldier(RebelSoldier* enemy) {
	if(player.getInTank()){
		loadEnemySensors(enemy, tankRef->getPos() + tankRef->getCollider().size / 2.f);
	}else{
		loadEnemySensors(enemy, player.getPos() + player.getCollider().size / 2.f);
	}
		
	if (CollisionManager::checkCollision(player.getCollider(), enemy->getCollider(), getResourceManager()) || (
		player.getInTank() && CollisionManager::checkCollision(tankRef->getCollider(), enemy->getCollider(), getResourceManager()))
	) {
		if(enemy->getAttacking()){
			damagePlayerOrTank();
		} 

		if(player.isShooting()){
			enemy->setAlive(false);
			player.addScore(100);
		}
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

		if (CollisionManager::checkCollision(g->getCollider(), player.getCollider(), getResourceManager(), 1)||
			(player.getInTank() && CollisionManager::checkCollision(g->getCollider(), tankRef->getCollider(), getResourceManager(),1))) {
			g->explode();
			damagePlayerOrTank();
		}
	}
}

void GameScene::handlePow(Pow* pow) {
	if (CollisionManager::checkCollision(player.getCollider(), pow->getCollider(), getResourceManager(),1)) {
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
}

void GameScene::handleLootDrop(Entity* e, const Collider& playerColliderInFront) {
	LootDrop* lootDrop = static_cast<LootDrop*>(e);
	
	if(e->getEntityType() == EntityType::ET_POWERUP){
		PowerUp* powerUp = static_cast<PowerUp*>(e);
		if(powerUp->getState() == PowerUpState::PUS_CRATE){
			if(player.isShooting() &&
			   (CollisionManager::checkCollision(player.getCollider(), lootDrop->getCollider(), getResourceManager(),1)||
			   CollisionManager::checkCollision(playerColliderInFront, lootDrop->getCollider(), getResourceManager()))
			){
				powerUp->setState(PowerUpState::PUS_REVEALED);
			}
		}
	}

	// DONE: Add player colllision resolution on lootdrop, it can walk over it
	if (CollisionManager::checkCollision(player.getCollider(), lootDrop->getCollider(), getResourceManager())) {
		CollisionManager::resolveCollisionAOverB(player, lootDrop->getCollider());
		lootDrop->applyEffect(player);
	}
}

void GameScene::handleHelicopter(Helicopter* h) {
	loadEnemySensors(h, player.getPos() + player.getCollider().size / 2.f);
	
	if(!h->getAlive()){
				getCamera().setWorldSize(vec2(static_cast<float>(nTilesLimit2Camera * map.getTileSize()), 
											  static_cast<float>(map.getTiles().y * map.getTileSize())));

	}

	for (int j = 0; j < h->getMaxBullets(); j++) {
		Bullet* b = h->getBullet(j);
		if (!b) continue;
		
		if (b->hasToBeFreed()) {
			h->freeBullet(j);
			continue;
		}
		if (b->getDisabled()) continue;
		
		if (getCamera().isOutOfView(b->getPos())) {
			b->explode();
		}
		
		if (CollisionManager::checkCollision(b->getCollider(), player.getCollider(), getResourceManager(),1)) {
			b->explode();
			player.takeHit();
		}
		if (CollisionManager::checkMapCollision(b->getCollider(), map.getLayer(MapLayerNames::MLN_COLLISION_LAYER), -1)) {
			b->explodeMap();
		}
		
		
	}
	h->addRenderDatas(getRenderer());
}

void GameScene::handleBoss(Boss* bs) {
	loadEnemySensors(bs, player.getPos() + player.getCollider().size / 2.f);

	for (int j = 0; j < bs->getMaxBullets(); j++) {
		Bullet* b = bs->getBullet(j);
		if (!b) continue;

		if (b->hasToBeFreed()) {
			bs->freeBullet(j);
			continue;
		}
		if (b->getDisabled()) continue;

		if (getCamera().isOutOfView(b->getPos())) {
			b->explode();
		}
		
		if (CollisionManager::checkCollision(b->getCollider(), player.getCollider(), getResourceManager(), 1) ||
			(player.getInTank() && CollisionManager::checkCollision(b->getCollider(), tankRef->getCollider(), getResourceManager(), 1))) {
			b->explode();
			damagePlayerOrTank();
		}
		if (CollisionManager::checkMapCollision(b->getCollider(), map.getLayer(MapLayerNames::MLN_COLLISION_LAYER), -1)) {
			b->explodeMap();
		}
	}	
	bs->addRenderDatas(getRenderer());
}

void GameScene::handleTank(Tank* tank) {
	if(!tank->hasPlayer() &&
		CollisionManager::checkCollision(player.getCollider(), tank->getCollider(), getResourceManager()) && player.getPos().y < tank->getPos().y){
		tank->enterPlayer(&player);
		printf("aaaa");
	}

	if(!tank->hasPlayer()){
		CollisionManager::resolveCollisionAOverB(player, tank->getCollider());
	}	
}


// ---------------------------------------------------------------------------
// Entity storage
// ---------------------------------------------------------------------------
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
	
// Deliberately NOT shifting the array after a free.
// Shifting every entity after the freed index to close the gap would cost
// up to O(n) pointer moves on every single despawn 
// Leaving the slot as nullptr costs O(1)
// to free, and the per-frame cost of scanning past empty slots it's far
// cheaper than the shifting we'd be doing to avoid it. Compacting would
// only pay off if MAXENTITIES were large enough.
void GameScene::freeEntity(int index) {
	if (spawnedEntities[index]) {
		if (spawnedEntities[index] == tankRef) {
			tankRef = nullptr;
		}
		delete spawnedEntities[index];
		spawnedEntities[index] = nullptr;
	}
}