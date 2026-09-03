#pragma once
class InputManager
{
public:
	InputManager();

	void addKeyPressed(char key);
	void removeKeyPressed(char key);

	bool isKeyPressed(char key);

	void getPressedKeys();

private:
	static const int KEYNUM = 512;
	char keys[KEYNUM];

};

