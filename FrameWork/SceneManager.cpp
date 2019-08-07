#include "SceneManager.h"

SceneManager* SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
	charles = new PlaySceneCharles();
	charlesBoss = new PlaySceneCharlesBoss();
	pittsburgh = new PlayScenePittsburgh();
	pittsburghPortal01 = new PlayScenePittsburghPortal01();
	pittsburghPortal02 = new PlayScenePittsburghPortal02();
	pittsburghBoss = new PlayScenePittsburghBoss();
	currentScene = nullptr;
	ReplaceScene(MapName::CHARLES);
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
	if (pittsburghPortal01 != nullptr)
		delete pittsburghPortal01;
	if (pittsburghPortal02 != nullptr)
		delete pittsburghPortal02;
	if (pittsburghBoss != nullptr)
		delete pittsburghBoss;
}

bool SceneManager::AddObjectToCurrentScene(Object *object)
{
	return currentScene->AddObjectToPlayScene(object);
}

void SceneManager::Update(double dt)
{

	MapName nextMap = currentScene->GetAndResetDestinationMap();
	bool isCurrentSceneDone = currentScene->isDone();
	//Kiểm tra xem nếu scene hiện tại đã xong rồi thì ta chuyển Scene.
	if (isRestartCurrentScene)
		ExecuteRestartCurrentScene();
	else if (!isCurrentSceneDone && nextMap == NOMAP) //Nếu vẫn là Scene hiện tại thì thôi.
		currentScene->Update(dt);
	else if (!isCurrentSceneDone) //Nếu chỉ muốn thay đổi Scene (khi vào portal).
	{
		ChangeScene(nextMap);
	}
	else if (isCurrentSceneDone) //Khi đã xong luôn rồi.
	{
		ReplaceScene(nextMap);
	}
	else
		currentScene->Update(dt);
}

PlayScene* SceneManager::fromMapNameToPlayScene(MapName mapName)
{
	PlayScene* nextScene = nullptr;
	if (mapName == MapName::CHARLES)
		nextScene = charles;
	else if (mapName == MapName::CHARLESBOSSLIGHT)
	{
		charlesBoss->setLightStatus(true);
		nextScene = charlesBoss;
	}
	else if (mapName == MapName::CHARLESBOSSDARK)
	{
		charlesBoss->setLightStatus(false);
		nextScene = charlesBoss;
	}
	else if (mapName == MapName::PITTSBURGHDARK)
	{
		pittsburgh->setLightStatus(false);
		nextScene = pittsburgh;
	}
	else if (mapName == MapName::PITTSBURGHLIGHT)
	{
		pittsburgh->setLightStatus(true);
		nextScene = pittsburgh;
	}
	else if (mapName == MapName::PITTSBURGHPORTAL1DARK)
	{
		pittsburghPortal01->setLightStatus(false);
		nextScene = pittsburghPortal01;
	}
	else if (mapName == MapName::PITTSBURGHPORTAL1LIGHT)
	{
		pittsburghPortal01->setLightStatus(true);
		nextScene = pittsburghPortal01;
	}
	else if (mapName == MapName::PITTSBURGHPORTAL2LIGHT)
	{
		pittsburghPortal02->setLightStatus(true);
		nextScene = pittsburghPortal02;
	}
	else if (mapName == MapName::PITTSBURGHPORTAL2DARK)
	{
		pittsburghPortal02->setLightStatus(false);
		nextScene = pittsburghPortal02;
	}
	else if (mapName == MapName::PITTSBURGHBOSS)
	{
		nextScene = pittsburghBoss;
	}

	return nextScene;
}

void SceneManager::ReplaceScene(MapName mapName)
{
	PlayScene* nextScene = fromMapNameToPlayScene(mapName);
	if (nextScene == nullptr)
		return;
	Camera::getCameraInstance()->ResetCameraPosition();
	if (currentScene != nullptr)
		delete currentScene;
	currentScene = nextScene;
	SoundManager::getinstance()->stopAll();
	if (currentScene == charles)
		SoundManager::getinstance()->play(SoundManager::SoundName::main_theme, true);
	if (currentScene == charlesBoss)
		SoundManager::getinstance()->play(SoundManager::SoundName::boss_wizard_theme, true);
	if (currentScene == pittsburgh)
		SoundManager::getinstance()->play(SoundManager::SoundName::main_theme, true);
	if (currentScene == pittsburghBoss)
		SoundManager::getinstance()->play(SoundManager::SoundName::boss_gragas_theme, true);

	currentScene->ResetPlayerPosition(); //Từng Scene sẽ có cách khởi tạo player ở những vị trí khác nhau. Vì vậy ta phải reset theo từng scene.
	currentScene->ResetCamera(); //Reset các thông số của Camera khi load map.
	//Khi replace scene thì ta cũng add luôn các phần tử liên quan đến player vào grid.
	currentScene->AddPlayerElementsToGrid();

}

//ChangeScene sẽ đổi Scene, nhưng sẽ giữ Scene trước đó (không delete) và trạng thái của player khi đang ở Scene đó.
void SceneManager::ChangeScene(MapName mapName)
{
	//Lưu lại thông tin của player hiện tại để phục vụ cho việc chuyển cảnh về sau trước khi đổi màn.
	Player * player = Player::getInstance();
	PlayerInfo playerInfo;
	CameraInfo cameraInfo;
	playerInfo.playerX = player->pos.x;
	playerInfo.playerY = player->pos.y;
	cameraInfo = Camera::getCameraInstance()->GetCurrentCameraPosition();

	playerSavedStatesWithPlayScene[currentScene] = playerInfo;
	cameraSavedStatesWithPlayScene[currentScene] = cameraInfo;

	PlayScene * nextScene = fromMapNameToPlayScene(mapName);
	if (nextScene == nullptr)
		return;

	currentScene = nextScene;
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
		player->SetOnAirState(Player::OnAir::None);
		Camera::getCameraInstance()->SetPosition(cameraSavedStatesWithPlayScene[currentScene]);
	}
	else
	{
		//Trong trường hợp không tìm thấy.
		//Thì ta reset luôn vị trí player về mặc định của map.
		currentScene->ResetPlayerPosition();
		//Khi replace scene thì ta cũng add luôn các phần tử liên quan đến player vào grid.
		currentScene->AddPlayerElementsToGrid();
	}
}

void SceneManager::GoToNextScene()
{
	currentScene->GoToNextScene();
}

void SceneManager::Draw()
{
	currentScene->Draw();
}

PlayScene* SceneManager::getCurrentScene()
{
	return currentScene;
}

void SceneManager::ExecuteRestartCurrentScene()
{
	if (currentScene == charles)
	{
		charles = new PlaySceneCharles();
		ReplaceScene(MapName::CHARLES);
	}
	else if (currentScene == charlesBoss)
	{
		charlesBoss = new PlaySceneCharlesBoss();
		ReplaceScene(MapName::CHARLESBOSSLIGHT);
	}
	else if (currentScene == pittsburgh)
	{
		pittsburgh = new PlayScenePittsburgh();
		ReplaceScene(MapName::PITTSBURGHDARK);
	}
	else if (currentScene == pittsburghBoss)
	{
		pittsburghBoss = new PlayScenePittsburghBoss();
		ReplaceScene(MapName::PITTSBURGHBOSS);
	}
	Player::getInstance()->SetHeart(Player::getInstance()->MAX_HEART);
	isRestartCurrentScene = false;
}

void SceneManager::RestartCurrentScene()
{
	isRestartCurrentScene = true;
}