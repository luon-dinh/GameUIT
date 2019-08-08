#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "KeyboardManager.h"
#include "PlaySceneCharles.h"
#include "PlaySceneCharlesBoss.h"
#include "PlayScenePittsburgh.h"
#include "PlayScenePittsburghPortal01.h"
#include "PlayScenePittsburghPortal02.h"
#include "PlayScenePittsburghBoss.h"
#include "PauseScene.h"

class SceneManager
{
public:

	static SceneManager* getInstance()
	{
		if (sceneManagerInstance == nullptr)
			sceneManagerInstance = new SceneManager();
		return sceneManagerInstance;
	}
	static void releaseInstance()
	{
		if (sceneManagerInstance != nullptr)
			delete sceneManagerInstance;
	}

	//Hàm dùng để lấy Scene hiện tại.
	PlayScene* getCurrentScene();

	//Hàm dùng để thêm một object vào Scene.
	bool AddObjectToCurrentScene(Object* object);

	//Hàm dùng để cập nhật Scene hiện tại.
	void Update(double dt);

	//Hàm dùng để vẽ những gì có trong Scene lên màn hình.
	void Draw();

	//Hàm dùng để bật tắt đèn cho Scene hiện tại.
	void TurnOnOffLight() { currentScene->TurnOnOffLight(); }

	//Hàm dùng để lấy tình trạng đèn đóm của Scene hiện tại.
	bool IsLightOn() { return currentScene->getLightStatus(); }

	//Hàm dùng để restart lại scene hiện tại.
	void RestartCurrentScene();

	//Hàm dùng để cho qua màn tiếp theo.
	void GoToNextScene();
private:
	//Biến dùng để xét xem hiện tại có restart scene hay không.
	bool isRestartCurrentScene = false;

	//Biến dùng để xét xem Scene hiện tại có phải đang được dừng lại hay không.
	bool isCurrentScenePaused = false;

	//Hàm thực thi việc restart scene hiện tại.
	void ExecuteRestartCurrentScene();

	static SceneManager * sceneManagerInstance;

	PlayScene* charles;
	PlaySceneCharlesBoss* charlesBoss;
	PlayScenePittsburgh* pittsburgh;
	PlayScenePittsburghPortal01* pittsburghPortal01;
	PlayScenePittsburghPortal02* pittsburghPortal02;
	PlayScenePittsburghBoss* pittsburghBoss;
	PauseScene* pauseScene;

	MapName sceneBeforePause;

	PlayScene* currentScene;

	//Lưu lại trạng thái của player trước khi chuyển màn để sau đó chuyển màn lại có thể để player ở vị trí chính xác.
	std::unordered_map<PlayScene*, PlayerInfo> playerSavedStatesWithPlayScene;

	//Lưu lại trạng thái của camera trước khi chuyển màn để sau đó chuyển màn lại có thể đặt camera ở vị trí chính xác.
	std::unordered_map<PlayScene*, CameraInfo> cameraSavedStatesWithPlayScene;

	SceneManager();
	~SceneManager();

	//Hàm dùng để gọi các thủ tục khi thay scene như cập nhật vị trí camera, player,...
	void ReplaceScene(MapName);
	//Hàm dùng để load một Scene khác.
	void ChangeScene(MapName);

	//Hàm dùng để xử lý từ tên map thành con trỏ Scene.
	PlayScene* fromMapNameToPlayScene(MapName);

	MapName fromPlaySceneToMapName(PlayScene*);
};