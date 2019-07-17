#include "SceneManager.h"

SceneManager* SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
	charles = new PlayScene01();
	charlesBoss = new PlayScene01Boss();
	ChangeScene(charles);
}

SceneManager::~SceneManager()
{
	//Xoá tất cả Scene đã được load lên.
	if (charles != nullptr)
		delete charles;
	if (charlesBoss != nullptr)
		delete charlesBoss;
	if (pittsburge != nullptr)
		delete pittsburge;
	if (pittsburgeBoss != nullptr)
		delete pittsburgeBoss;
}

void SceneManager::Update(double dt)
{
	//Kiểm tra xem nếu scene hiện tại đã xong rồi thì ta chuyển Scene.
	if (!currentScene->isDone())
		currentScene->Update(dt);
	else
		ChangeScene(charlesBoss);
}

void SceneManager::ChangeScene(PlayScene* newScene)
{
	currentScene = newScene;
	currentScene->ResetCamera(); //Reset các thông số của Camera khi load map.

	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 0;
	player->pos.y = SCREEN_HEIGHT;
}

void SceneManager::Draw()
{
	currentScene->Draw();
}

void SceneManager::ReplaceScreen(PlayScene * newScene)
{
	currentScene = newScene;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}
