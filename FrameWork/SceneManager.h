#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "KeyboardManager.h"
#include "PlaySceneCharles.h"
#include "PlaySceneCharlesBoss.h"
#include "PlayScenePittsburgh.h"
#include "PlayScenePittsburghPortal01.h"
#include "PlayScenePittsburghPortal02.h"

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

	//Hàm dùng để cho qua màn tiếp theo.
	void GoToNextScene();
private:
	static SceneManager * sceneManagerInstance;

	PlayScene* charles;
	PlaySceneCharlesBoss* charlesBoss;
	PlayScenePittsburgh* pittsburgh;
	PlayScenePittsburghPortal01* pittsburghPortal01;
	PlayScenePittsburghPortal02* pittsburghPortal02;

	PlayScene* pittsburghBoss;
	PlayScene* currentScene;

	//Lưu lại trạng thái của player trước khi chuyển màn để sau đó chuyển màn lại có thể để player ở vị trí chính xác.
	std::unordered_map<PlayScene*, PlayerInfo> playerSavedStatesWithPlayScene;

	SceneManager();
	~SceneManager();

	//Hàm dùng để gọi các thủ tục khi thay scene như cập nhật vị trí camera, player,...
	void ReplaceScene(MapName);
	//Hàm dùng để load một Scene khác.
	void ChangeScene(MapName);

	//Hàm dùng để xử lý từ tên map thành con trỏ Scene.
	PlayScene* fromMapNameToPlayScene(MapName);
};