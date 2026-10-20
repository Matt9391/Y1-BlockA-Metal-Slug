#include "precomp.h"
#include "CustomScene.h"
#include <surface.h>
#include <Renderer.h>
#include <TypeScene.h>

CustomScene::CustomScene(Surface* screen, Renderer& renderer_, InputManager& inputManager_, AudioManager& audioManager_, ResourceManager& resourceManager_) :
	renderer(renderer_),
	inputManager(inputManager_),
	audioManager(audioManager_),
	resourceManager(resourceManager_),
	camera(vec2(0,0), vec2(static_cast<float>(screen->width), static_cast<float>(screen->height))),
	changeScene(false),
	nextScene(TypeScene::MENU),
	firstFrame(true)

{

}

vec2 CustomScene::getCameraPos() const {
	return camera.getPos();
}

Renderer& CustomScene::getRenderer() const{
	return this->renderer;
}
ResourceManager& CustomScene::getResourceManager() const{
	return this->resourceManager;
}

InputManager& CustomScene::getInputManager() const{
	return this->inputManager;
}

AudioManager& CustomScene::getAudioManager() const{
	return this->audioManager;
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


void CustomScene::setFirstFrame(bool firstFrame_){
	this->firstFrame = firstFrame_;
}
bool CustomScene::isFirstFrame() const{
	return this->firstFrame;
}