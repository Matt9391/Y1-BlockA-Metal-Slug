#include "precomp.h"
#include "Renderer.h"
#include <ResourceManager.h>
#include <iostream>


Renderer::Renderer() :
	renderSetCount(0)
	{}

void Renderer::addRenderSet(RenderSet rs) {
	renderSets[renderSetCount++] = rs;
	
}

void Renderer::clearRenderSets() {
	for (int i = 0; i < MAXRENDERSETS; i++) {
		renderSets[i] = RenderSet();
	}
}

void Renderer::render(Surface* screen, const ResourceManager& resourceManager) {

	for (int i = 0; i < renderSetCount; i++) {
		RenderSet& rs = this->renderSets[i];

		for (int j = 1; j < rs.animationSet.layerCount; j++) {
			AnimationLayer& layer = rs.animationSet.layers[j];
			Sprite* sprite = resourceManager.getSprite(layer.resourceId);
			std::cout << layer.currentFrame << std::endl;
			//if (layer.currentFrame == 0) 
			//	continue;
			sprite->SetFrame(layer.currentFrame);
			//sprite->Draw(screen, rs.pos.x + layer.offset.x, rs.pos.y + layer.offset.y);
			sprite->DrawScaled(screen, rs.pos.x + layer.offset.x, rs.pos.y + layer.offset.y, 6);
		}

	}
}