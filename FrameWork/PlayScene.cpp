#include "PlayScene.h"
#include "Debug.h"
#include <dinput.h>

PlayScene::~PlayScene()
{
	if (world11 != nullptr)
		delete world11;
	if (camera != nullptr)
		camera->ReleaseCameraInstance();
}

PlayScene::PlayScene()
{
	LoadContent();
}

void PlayScene::LoadContent()
{
	world11 = new GameMap(world11tile,world11map, world11MapObject);
	camera = Camera::getCameraInstance();
	world11->SetCamera(camera);
	camera->SetMapProperties(world11->getMapHeight(), world11->getMapWidth());
	mapStaticObject = world11->getStaticObject();
}

void PlayScene::Draw()
{
	world11->Draw();
}

void PlayScene::Update(double dt)
{
	//Xử lý input và move camera (nếu có).
	ProcessKeyBoardInput(dt);
	UpdateCameraWithPlayerPos(dt);
	//Kiểm tra va chạm.
	CollisionProcess(dt);
	//Thêm gia tốc (ngoại cảnh tác động nhân vật).

}

void PlayScene::EnvironmentUpdate(double dt)
{

}

void PlayScene::CollisionProcess(double dt)
{
	////Kiểm tra collision với ground.
	//for (int i = 0; i < mapStaticObject.size(); ++i)
	//{
	//	//Lấy BoxRect của Player.
	//	BoundingBox playerBox = player->GetBoundingBox();
	//	BoundingBox objectBox = mapStaticObject[i]->GetBoundingBox();
	//	collisionOut colOut = Collision::getInstance()->SweptAABB(playerBox, objectBox);
	//	
	//}
}

void PlayScene::ProcessKeyBoardInput(double dt)
{
	ProcessKeyBoardInput(dt);
	KeyboardManager* inputInstance = KeyboardManager::getInstance();

	if (inputInstance->isKeyDown(DIK_LEFT))
	{
		PrintDebug("LEFT\n");
		camera->MoveLeft();
	}

	if (inputInstance->isKeyDown(DIK_RIGHT))
	{
		PrintDebug("RIGHT\n");
		camera->MoveRight();
	}

	if (inputInstance->isKeyDown(DIK_UP))
	{
		PrintDebug("UP\n");
		camera->MoveUp();
	}

	if (inputInstance->isKeyDown(DIK_DOWN))
	{
		PrintDebug("DOWN\n");
		camera->MoveDown();
	}
}

void PlayScene::UpdateCameraWithPlayerPos(double dt)
{

}