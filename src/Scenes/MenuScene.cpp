#include "precomp.h"
#include "MenuScene.h"

#include <Renderer.h>
#include <InputManager.h>
#include <ResourceIDFrames.h>
#include <TypeScene.h>

MenuScene::MenuScene(Surface* screen, Renderer& renderer, InputManager& inputManager) :
	CustomScene(screen,renderer,inputManager),
	secondsLeft(60),
	elapsedTime(0.f)
{}

void MenuScene::init() {
	getRenderer().addRenderSet(RenderSet(
		AnimationSet(
			1,
			AnimationLayer(
				ResourceID::ID_MENU_BG,
				ResourceIDFrames::IDF_MENU_BG,
				100.f,
				vec2(0,0), vec2(0,0))),
		vec2(0,0)
	));
	
	secondsLeft = 60;
	elapsedTime = 0.f;

	setNextScene(TypeScene::GAMEPLAY);

}

void MenuScene::exit() {};

void MenuScene::update(float dt) {
	elapsedTime += dt;
	if (elapsedTime > 1000.f) {
		elapsedTime = 0.f;
		secondsLeft--;
	}

	if (secondsLeft == 0 || getInputManager().isKeyPressed(' ')) {
		setChangeScene(true);
	}

	getRenderer().clearTexts();

	char timeLeft[15];
	snprintf(timeLeft, sizeof(timeLeft), "TIME %d", secondsLeft);
	getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_ORANGE_S, timeLeft, vec2(130, 155),1.f });
	if(elapsedTime > 500.f)
		getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY, "PUSH P1 START!", vec2(50, 170),0.8f });
	getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "1996 NAZCA CORPORATION", vec2(50, 190),1.f });
	getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "LEVEL-4", vec2(150, 215),1.f });
	getRenderer().addHUDText(HUDText{ ResourceID::ID_FONT_GREY_S, "CREDIT 01", vec2(220, 215),1.f });

}

void MenuScene::display(float dt) {

}
