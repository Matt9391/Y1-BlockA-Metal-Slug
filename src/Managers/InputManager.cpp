#include "precomp.h"
#include "InputManager.h"

InputManager::InputManager() 
	{
		for (int i = 0; i < KEYNUM; i++) {
			keys[i] = 0;
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

void InputManager::getPressedKeys() {
	for (int i = 0; i < KEYNUM; i++) {
		if (keys[i] == 1) {
			printf("k: %c\n", i);
		}
	}

}

