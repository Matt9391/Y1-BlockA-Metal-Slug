#include "precomp.h"
#include "InputManager.h"

InputManager::InputManager() 
	{
		for (int i = 0; i < KEYNUM; i++) {
			keys[i] = 0;
			previousKeys[i] = 0;
		}
		
	}

void InputManager::updateLastFrameKeys() {
	for (int i = 0; i < KEYNUM; i++) {
		previousKeys[i] = keys[i];
	}
}

void InputManager::addKeyPressed(char key) {
	keys[key & 511] = 1;
}

void InputManager::removeKeyPressed(char key) {
	keys[key & 511] = 0;
}

bool InputManager::isKeyPressed(char key) const {
	return keys[key & 511] == 1;
}

bool InputManager::isKeyJustPressed(char key) const {
	return keys[key & 511] == 1 && previousKeys[key & 511] != keys[key & 511];
}

