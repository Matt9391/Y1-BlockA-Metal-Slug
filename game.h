// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once
#include "InputManager.h"
#include <SceneManager.h>
#include <ResourceManager.h>
#include <Renderer.h>

namespace Tmpl8
{

class Game : public TheApp
{
public:
	Game();
	~Game();
	// game flow methods
	void Init();
	void Tick( float dt );
	void Shutdown() { printf("shutdown");/* implement if you want to do something on exit */ }
	// input handling
	void MouseUp( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel( float ) { /* implement if you want to handle the mouse wheel */ }
	void KeyUp(int key) { inputManager.removeKeyPressed(static_cast<char>(key)); }
	void KeyDown(int key) { inputManager.addKeyPressed(static_cast<char>(key)); }
	// data members
	int2 mousePos;
	
	InputManager inputManager;
	ResourceManager resourceManager;
	SceneManager sceneManager;
	Renderer renderer;

};

} // namespace Tmpl8