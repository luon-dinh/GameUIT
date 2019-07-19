#include "Game.h"
Game::Game(HWND hwnd,HINSTANCE hInstance)
{
	this->Init(hwnd, hInstance);
	this->LoadResources();
}

Game::~Game()
{

}

void Game::Init(HWND hwnd, HINSTANCE hInstance)
{
	auto d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;


	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	D3DXCreateSprite(d3ddev, &spriteHandler);
	KeyboardManager::getInstance()->Create(hInstance, hwnd);


	SoundManager::getinstance()->Create(hwnd);
}
void Game::LoadResources()
{
	TextureManager::getInstance()->loadResources();
	SpriteManager::getInstance()->LoadResources();
	SoundManager::getinstance()->loadResources();
	SceneManager::getInstance();
}
void Game::Run()
{
	MSG msg;
	auto frameStart = GetTickCount();
	auto tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (true)
	{
		if (PeekMessage(&msg,NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		auto now = GetTickCount();
		auto dt = now - frameStart;

		if (dt > tickPerFrame)
		{
			frameStart = now;
			KeyboardManager::getInstance()->getState(dt);
			Update(dt);
			// chac bat key handler o day
			ProcessAllInput();
			Render();
		}
		//else
		//{
		//	Sleep(tickPerFrame - dt);
		//}
	}
}

void Game::ProcessAllInput()
{

}

void Game::Update(float dt)
{
	SceneManager::getInstance()->Update(dt);
}
void Game::Render()
{
	//d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR(D3DCOLOR_XRGB(255, 0, 255)), 1, NULL);
	while (!d3ddev->BeginScene());
	while (!spriteHandler->Begin(D3DXSPRITE_ALPHABLEND));
	SceneManager::getInstance()->Draw();
	spriteHandler->End();
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

