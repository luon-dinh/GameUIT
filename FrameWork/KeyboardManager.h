#pragma once
#include"Global.h"
class KeyboardManager
{
private:
	LPDIRECTINPUT8 di8;
	LPDIRECTINPUTDEVICE8 did8;
	char key_buffer[256];
	bool clickedKeys[256] = { 0 };
	bool activatedKeys[256] = { 0 }; //Dùng để lấy các phím đang được nhấn trong vòng lặp này.
	bool prevClicked[256] = { 0 };
	int timeSinceLastClicked[256] = { 0 };
	static KeyboardManager* instance;
public:
	void Create(HINSTANCE hInstance,HWND hwnd);
	static KeyboardManager* getInstance();
	void getState(double dt);
	bool isKeyDown(int key);
	bool getKeyPressedOnce(int key);
	bool getKeyPressedOnce(int key, int& timeSinceLastPressed);
	bool isKeyUp(int key);
	KeyboardManager();
	~KeyboardManager();
};

