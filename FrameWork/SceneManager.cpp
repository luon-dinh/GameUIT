#include "SceneManager.h"

SceneManager* SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
	charles = new PlaySceneCharles();
	charlesBoss = new PlaySceneCharlesBoss();
	pittsburgh = new PlayScenePittsburgh();
	currentScene = nullptr;
	ReplaceScene(charles);
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
	else if (currentScene == charles)
		ReplaceScene(charlesBoss);
	else if (currentScene == charlesBoss)
		ReplaceScene(pittsburgh);
	else
		currentScene->Update(dt);
}

void SceneManager::ReplaceScene(PlayScene* newScene)
{
	if (currentScene != nullptr)
		delete currentScene;
	currentScene = newScene;
	currentScene->ResetCamera(); //Reset các thông số của Camera khi load map.
	currentScene->ResetPlayerPosition(); //Từng Scene sẽ có cách khởi tạo player ở những vị trí khác nhau. Vì vậy ta phải reset theo từng scene.
}

//ChangeScene sẽ đổi Scene, nhưng sẽ giữ Scene trước đó (không delete) và trạng thái của player khi đang ở Scene đó.
void SceneManager::ChangeScene(PlayScene * newScene)
{
	//Lưu lại thông tin của player hiện tại để phục vụ cho việc chuyển cảnh về sau trước khi đổi màn.
	Player * player = Player::getInstance();
	PlayerInfo playerInfo;
	playerInfo.playerX = player->pos.x;
	playerInfo.playerY = player->pos.y;

	playerSavedStatesWithPlayScene[currentScene] = playerInfo;

	currentScene = newScene;
	currentScene->ResetCamera(); //Reset các thông số của Camera khi load map.

	//Khôi phục lại vị trí player.
	//Thử tìm xem có thấy info trước đó không.
	if (playerSavedStatesWithPlayScene.find(currentScene) != playerSavedStatesWithPlayScene.end())
	{
		//Trong trường hợp tìm thấy thì ta trả vị trí của player về lại trước khi chuyển Scene.
		PlayerInfo prevInfo = playerSavedStatesWithPlayScene[currentScene];
		player->pos.x = prevInfo.playerX;
		player->pos.y = prevInfo.playerY;
		player->ChangeState(State::STANDING);
		player->SetAirState(Player::OnAir::None);
	}
	else
	{
		//Trong trường hợp không tìm thấy.
		//Thì ta reset luôn vị trí player về mặc định của map.
		currentScene->ResetPlayerPosition();
	}
}

void SceneManager::Draw()
{
	currentScene->Draw();
}



Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}
