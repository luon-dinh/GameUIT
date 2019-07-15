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
	mapStaticObject = world11->getStaticObject(); //Lấy entity của tất cả các object.

	player = Player::getInstance(); //Lấy instance của player.
}

void PlayScene::Draw()
{
	world11->Draw();
}

void PlayScene::Update(double dt)
{
	//Xử lý input và move camera (nếu có).
	ProcessKeyBoardInput(dt);
	//Kiểm tra va chạm.
	CollisionProcess(dt);

	//Sau khi xử lý input và kiểm tra va chạm thì mình mới Update lại Camera dựa trên vị trí mới của player.
	UpdateCameraWithPlayerPos(dt);

	//Thêm gia tốc (ngoại cảnh tác động nhân vật).
}

void PlayScene::UpdateCameraWithPlayerPos(double dt)
{
	float playerPosX = 0;
	float playerPosY = 0;

	RECT cameraBoundBox = Camera::getCameraInstance()->getBoundingBox();

	int leftBound = cameraBoundBox.left;
	int rightBound = cameraBoundBox.right;
	int topBound = cameraBoundBox.top;
	int bottomBound = cameraBoundBox.bottom;

	//Chúng ta sẽ chỉnh lại Camera sao cho khi Player rời khỏi vị trí Critical Line, Camera sẽ bám theo.
	float deltaMoveCamLeft = leftBound - (playerPosX - player->width / 2);
	float deltaMoveCamRight = (playerPosX + player->width / 2) - rightBound;
	float deltaMoveCamTop = (playerPosY + player->height / 2) - topBound;
	float deltaMoveCamBottom = topBound - (playerPosY - player->height / 2);

	if (deltaMoveCamLeft > 0)
		camera->MoveLeft(deltaMoveCamLeft);
	else if (deltaMoveCamRight > 0)
		camera->MoveRight(deltaMoveCamRight);

	if (deltaMoveCamTop > 0)
		camera->MoveUp(deltaMoveCamTop);
	else if (deltaMoveCamBottom > 0)
		camera->MoveDown(deltaMoveCamBottom);

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