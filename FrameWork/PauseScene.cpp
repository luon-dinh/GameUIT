#include "PauseScene.h"

PauseScene::PauseScene()
{
	TextureManager::getInstance()->addTexture(Tag::PAUSESCENE, pathToPauseBackground);
	backgroundImage = new Sprite(Tag::PAUSESCENE, 0, 0, 224, 256);
}

PauseScene::~PauseScene()
{
	delete backgroundImage;
}

void PauseScene::Update(double dt)
{

}

void PauseScene::Draw()
{
	int playerScore = Player::getInstance()->GetScore();
	int playerHealth = Player::getInstance()->GetHealth();
	backgroundImage->Render(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
}