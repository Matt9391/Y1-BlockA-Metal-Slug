// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include <iostream>
#include <TypeScene.h>
#include <time.h>
// #include "vld.h"

Game::Game() :
	sceneManager(),
	resourceManager()
{
}

// TODO: 
Game::~Game() { 
	printf("game destruc"); 
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------

void Game::Init()
{
	resourceManager.init();
	sceneManager.init(screen, renderer, inputManager, resourceManager, audioManager, TypeScene::MENU);
}


// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float dt)
{
	//inputManager.getPressedKeys();
	screen->Clear(0xFFffff00);
	
	audioManager.clearSounds();

	sceneManager.getCurrentScene().update(dt);

	audioManager.playSounds(resourceManager);
	audioManager.playMusic();

	audioManager.updateSounds();

	renderer.render(screen, resourceManager, sceneManager.getCurrentScene().getCameraPos());

	inputManager.updateLastFrameKeys();

	if (sceneManager.getCurrentScene().sceneHasToChange()) {
		sceneManager.changeScene(sceneManager.getCurrentScene().getNextScene(), screen, renderer, inputManager, resourceManager, audioManager);
	}
}

