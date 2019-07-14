#pragma once
#include"Global.h"
class KeyboardManager
{
private:
	LPDIRECTINPUT8 di8;
	LPDIRECTINPUTDEVICE8 did8;
	char key_buffer[256];
	static KeyboardManager* instance;
public:
	void Create(HINSTANCE hInstance,HWND hwnd);
	static KeyboardManager* getInstance();
	void getState();
	bool isKeyDown(int key);
	KeyboardManager();
	~KeyboardManager();
};

