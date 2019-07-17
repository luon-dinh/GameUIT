#include "SceneManager.h"

SceneManager* SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
	currentScene = new PlayScene01();
}

SceneManager::~SceneManager()
{
	if (currentScene != nullptr)
		delete currentScene;
}

void SceneManager::Update(double dt)
{
	currentScene->Update(dt);
}

void SceneManager::Draw()
{
	currentScene->Draw();
}

void SceneManager::ReplaceScreen(Scene * newScene)
{
	if (currentScene != nullptr)
		delete currentScene;
	currentScene = newScene;
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}
