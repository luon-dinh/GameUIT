#pragma once
#include"Global.h"
#include"TextureManager.h"
#include<WinUser.h>
#include "SceneManager.h"
#include"KeyboardManager.h"
#include"Sprite.h"
#include"SoundManager.h"
#include"Player.h"
#include"SceneManager.h"
#include"PlayScene.h"
class Game {
private:
	LPDIRECTINPUT8 di8;										       
	LPDIRECTINPUTDEVICE8 did8;								
	char key_buffer[256];
public:
	Game(HWND hwnd, HINSTANCE hInstance);				
	void Init(HWND hwnd, HINSTANCE hInstance);
	void LoadResources();
	void Run();						
	void Update(float dt);	
	void ProcessAllInput();
	void Render();					
	~Game();
};