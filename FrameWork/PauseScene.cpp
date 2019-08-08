#include "PauseScene.h"
#include <string>

PauseScene::PauseScene()
{
	TextureManager::getInstance()->addTexture(Tag::PAUSESCENE, pathToPauseBackground);
	backgroundImage = new Sprite(Tag::PAUSESCENE, 0, 0, 224, 256);
	D3DXCreateFont(d3ddev, fontHeight, 0, FW_BOLD, -1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
	rectOfPlayerHealth.left = 150;
	rectOfPlayerHealth.right = 170;
	rectOfPlayerHealth.top = 44;
	rectOfPlayerHealth.bottom = rectOfPlayerHealth.top + fontHeight;
}

PauseScene::~PauseScene()
{
	delete backgroundImage;
	if (font)
	{
		font->Release();
		font = NULL;
	}
}

void PauseScene::Update(double dt)
{
	int playerScore = Player::getInstance()->GetScore();
	int playerHealth = Player::getInstance()->GetHealth();
	sPlayerScore = std::to_string(playerScore);
	sPlayerHealth = std::to_string(playerHealth);
	
}

void PauseScene::Draw()
{
	backgroundImage->Render(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
}

void PauseScene::RenderText()
{
	const char * scoreToDraw = sPlayerScore.c_str();
	const char * healthToDraw = sPlayerHealth.c_str();
	font->DrawTextA(NULL, scoreToDraw, -1, &rectOfPlayerHealth, DT_LEFT | DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
}