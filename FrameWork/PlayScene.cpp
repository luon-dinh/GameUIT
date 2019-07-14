#include "PlayScene.h"

PlayScene::PlayScene(int level)
{
	map = MapManager::getInstance()->getMap(level);

	p = Player::getInstance();
	Camera::GetInstance()->x = 0;
	Camera::GetInstance()->y = SCREEN_HEIGHT;


	switch (level)
	{
	case 1:
		endRect = Rect(9000, 4, 120, 16);
		break;

	case 2:
		endRect = Rect(3050, 65, 22, 35);
		break;

	case 3:
		endRect = Rect(0,0,0,0);
		break;
	}
}

PlayScene::~PlayScene()
{
	
}


void PlayScene::Update(float dt)
{
	auto camera = Camera::GetInstance();
	camera->x = p->posX - (camera->width >> 1);
	map->Update();
	
}

void PlayScene::Render()
{
	map->Render();
	p->Render();
}


void PlayScene::OnKeyDown()
{
	
}
void PlayScene::OnKeyUp()
{
	
}