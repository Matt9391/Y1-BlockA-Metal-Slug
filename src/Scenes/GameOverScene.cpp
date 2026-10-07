#include "precomp.h"
#include "GameOverScene.h"

#include <Renderer.h>
#include <InputManager.h>
#include <ResourceIDFrames.h>
#include <TypeScene.h>

GameOverScene::GameOverScene(Surface* screen, Renderer& renderer, InputManager& inputManager, AudioManager& audioManager) :
	CustomScene(screen,renderer,inputManager, audioManager),
	secondsLeft(60),
	elapsedTime(0.f)
{}

void GameOverScene::init() {
	getCamera().enableCamera(false);
	getRenderer().clearSpriteSets();
	getRenderer().addSpriteSet(SpriteSet(
				ResourceID::ID_GAME_OVER_BG,
				ResourceIDFrames::IDF_GAME_OVER_BG,
				vec2(0,0)));

	secondsLeft = 5;
	elapsedTime = 0.f;

	setNextScene(TypeScene::MENU);
	setChangeScene(false);
}

void GameOverScene::exit() {};

void GameOverScene::update(float dt) {
	elapsedTime += dt;
	if (elapsedTime > 1000.f) {
		elapsedTime = 0.f;
		secondsLeft--;
	}

	if (secondsLeft == 0 || getInputManager().isKeyJustPressed(' ')) {
		setChangeScene(true);
	}

	getRenderer().clearTexts();
}
