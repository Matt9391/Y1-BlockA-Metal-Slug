// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include <iostream>
#include <TypeScene.h>


Game::Game() :
	sceneManager()
{
}

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------

void Game::Init()
{
	sceneManager.init(screen, TypeScene::GAMEPLAY);
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float dt)
{
	sceneManager.getCurrentScene().display();
	screen->Box(100,100,screen->width,screen->height,0xffff0000);
}

