#include "SceneManager.h"
#include "TextureManager.h"
#include "KeyboardManager.h"
#include "TestScene.h"

SceneManager* SceneManager::sceneManagerInstance = nullptr;

SceneManager::SceneManager()
{
	currentScene = new TestScene();
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
