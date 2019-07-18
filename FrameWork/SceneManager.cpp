#include "SceneManager.h"

SceneManager* SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
	charles = new PlaySceneCharles();
	charlesBoss = new PlaySceneCharlesBoss();
	currentScene = nullptr;
	ReplaceScene(charles);
	Player * player = Player::getInstance();
	player->pos.x = 50;
}

SceneManager::~SceneManager()
{
	//Xoá tất cả Scene đã được load lên.
	if (charles != nullptr)
		delete charles;
	if (charlesBoss != nullptr)
		delete charlesBoss;
	if (pittsburgh != nullptr)
		delete pittsburgh;
	if (pittsburghBoss != nullptr)
		delete pittsburghBoss;
}

void SceneManager::Update(double dt)
{
	//Kiểm tra xem nếu scene hiện tại đã xong rồi thì ta chuyển Scene.
	if (!currentScene->isDone())
		currentScene->Update(dt);
	else
		ReplaceScene(charlesBoss);
}

void SceneManager::ReplaceScene(PlayScene* newScene)
{
	if (currentScene != nullptr)
		delete currentScene;
	currentScene = newScene;
	currentScene->ResetCamera(); //Reset các thông số của Camera khi load map.

	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 0;
	player->pos.y = SCREEN_HEIGHT;
	player->ChangeState(State::JUMPING);
	player->SetAirState(Player::OnAir::Falling);
}

void SceneManager::ChangeScene(PlayScene * newScene)
{
	currentScene = newScene;
}

void SceneManager::Draw()
{
	currentScene->Draw();
}



Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}
