#pragma once
#include "Sprite.h"
#include "TextureManager.h"
#include "KeyboardManager.h"
#include "PlaySceneCharles.h"
#include "PlaySceneCharlesBoss.h"
#include "PlayScenePittsburgh.h"

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
	Scene* getCurrentScene();

	//Hàm dùng để cập nhật Scene hiện tại.
	void Update(double dt);
	
	//Hàm dùng để load một Scene khác.
	void ChangeScene(PlayScene *);


	//Hàm dùng để vẽ những gì có trong Scene lên màn hình.
	void Draw();

private:
	static SceneManager * sceneManagerInstance;
	PlayScene* charles;
	PlayScene* charlesBoss;
	PlayScene* pittsburgh;
	PlayScene* pittsburghBoss;
	PlayScene* currentScene;
	SceneManager();
	~SceneManager();

	//Hàm dùng để gọi các thủ tục khi thay scene như cập nhật vị trí camera, player,...
	void ReplaceScene(PlayScene * newScene);
};