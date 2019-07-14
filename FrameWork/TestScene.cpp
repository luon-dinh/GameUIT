#include "TestScene.h"
#include "Debug.h"
#include <dinput.h>

TestScene::~TestScene()
{
	if (world11 != nullptr)
		delete world11;
	if (camera != nullptr)
		camera->ReleaseCameraInstance();
}

TestScene::TestScene()
{
	LoadContent();
}

void TestScene::LoadContent()
{
	world11 = new GameMap(world11tile,world11map);
	camera = Camera::getCameraInstance();
	world11->SetCamera(camera);
	camera->SetMapProperties(world11->getMapHeight(), world11->getMapWidth());
}

void TestScene::Draw()
{
	world11->Draw();
}

void TestScene::Update(double dt)
{
	//Xử lý input.
	InputManager* inputInstance = InputManager::getInputInstance();

	if (inputInstance->GetKey(DIK_LEFT))
	{
		PrintDebug("LEFT\n");
		camera->MoveLeft();
	}

	if (inputInstance->GetKey(DIK_RIGHT))
	{
		PrintDebug("RIGHT\n");
		camera->MoveRight();
	}

	if (inputInstance->GetKey(DIK_UP))
	{
		PrintDebug("UP\n");
		camera->MoveUp();
	}

	if (inputInstance->GetKey(DIK_DOWN))
	{
		PrintDebug("DOWN\n");
		camera->MoveDown();
	}
}