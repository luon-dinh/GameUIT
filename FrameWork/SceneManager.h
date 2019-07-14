#pragma once
#include "Sprite.h"
#include "Scene.h"

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
	void ReplaceScreen(Scene *);

	//Hàm dùng để vẽ những gì có trong Scene lên màn hình.
	void Draw();

private:
	static SceneManager * sceneManagerInstance;
	Scene* currentScene;
	SceneManager();
	~SceneManager();
};