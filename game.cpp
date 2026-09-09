// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include <iostream>
#include <TypeScene.h>


Game::Game() :
	sceneManager(),
	resourceManager()
{
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------

void Game::Init()
{
	resourceManager.init();
	sceneManager.init(screen, renderer, TypeScene::GAMEPLAY);
}


// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float dt)
{
	//inputManager.getPressedKeys();
	screen->Clear(0xFF00ff00);
	sceneManager.getCurrentScene().update(dt);
	renderer.render(screen, resourceManager);
	screen->Box(100,100,screen->width,screen->height,0xff0000);
	Sprite* spr = resourceManager.getSprite(ResourceID::ID_PLAYER_IDLE_BODY);
	spr->SetFrame(0);
	spr->DrawScaled(screen, 300, 300, 6);
}

