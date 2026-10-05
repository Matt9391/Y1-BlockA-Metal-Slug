#include "precomp.h"
#include "CustomScene.h"
#include <surface.h>
#include <Renderer.h>
#include <TypeScene.h>

CustomScene::CustomScene(Surface* screen, Renderer& renderer, InputManager& inputManager) :
	renderer(renderer),
	inputManager(inputManager),
	camera(vec2(0,0), vec2(static_cast<float>(screen->width), static_cast<float>(screen->height))),
	changeScene(false),
	nextScene(TypeScene::MENU)

{

}

vec2 CustomScene::getCameraPos() const {
	return camera.getPos();
}

Renderer& CustomScene::getRenderer() const{
	return this->renderer;
}

InputManager& CustomScene::getInputManager() const{
	return this->inputManager;
}

Camera& CustomScene::getCamera() {
	return this->camera;
}


TypeScene CustomScene::getNextScene() const {
	return this->nextScene;
}
bool CustomScene::sceneHasToChange() const {
	return changeScene;
}

void CustomScene::setNextScene(TypeScene nextScene_){
	this->nextScene = nextScene_;
}
void CustomScene::setChangeScene(bool changeScene_) {
	this->changeScene = changeScene_;
}