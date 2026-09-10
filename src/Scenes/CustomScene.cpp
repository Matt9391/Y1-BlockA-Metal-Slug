#include "precomp.h"
#include "CustomScene.h"
#include <surface.h>
#include <Renderer.h>

CustomScene::CustomScene(Surface* screen, Renderer& renderer) :
	screen(screen),
	renderer(renderer),
	camera(vec2(0,0), vec2(screen->width, screen->height))

{

}

vec2 CustomScene::getCameraPos() const {
	return camera.getPos();
}