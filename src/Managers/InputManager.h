#pragma once
class InputManager
{
public:
	InputManager();

	void updateLastFrameKeys();
	void addKeyPressed(char key);
	void removeKeyPressed(char key);

	bool isKeyPressed(char key) const;
	bool isKeyJustPressed(char key) const;

	void getPressedKeys();

private:
	static const int KEYNUM = 512;
	char keys[KEYNUM];
	char previousKeys[KEYNUM];

};

