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
	player->Render();
}

void PlayScene::Update(double dt)
{
	//Update map trước.
	world11->Update(dt);

	//Kiểm tra va chạm.
	CollisionProcess(dt);

	//Xử lý input và cập nhật (nếu có) cho các đối tượng mà PlayScene quản lý.
	//(Thông thường chỉ có player).
	ProcessUpdates(dt);

	//Sau khi xử lý input và kiểm tra va chạm thì mình mới Update lại Camera dựa trên vị trí mới của player.
	UpdateCameraWithPlayerPos(dt); 

	//Thêm gia tốc (ngoại cảnh tác động nhân vật).
}

void PlayScene::UpdateCameraWithPlayerPos(double dt)
{
	D3DXVECTOR2 playerPos = player->pos;

	int playerWidth = player->getWidth();
	int playerHeight = player->getHeight();

	RECT cameraBoundBox = Camera::getCameraInstance()->getBoundingBox();

	//Chuyển player từ world view sang view port để xét với các bound.
	D3DXVECTOR3 playerViewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(playerPos.x, playerPos.y, 0));

	int leftBound = cameraBoundBox.left;
	int rightBound = cameraBoundBox.right;
	int topBound = cameraBoundBox.top;
	int bottomBound = cameraBoundBox.bottom;

	//Chúng ta sẽ chỉnh lại Camera sao cho khi Player rời khỏi vị trí Critical Line, Camera sẽ bám theo.
	//Đầu tiên chúng ta xem player đang cách các cạnh của player một khoảng bao nhiêu.
	int fromPlayerToTop = playerViewPort.y - playerHeight / 2;
	int fromPlayerToBottom = SCREEN_HEIGHT - playerViewPort.y + playerHeight / 2;
	int fromPlayerToLeft = playerViewPort.x - playerWidth / 2;
	int fromPlayerToRight = SCREEN_WIDTH - playerViewPort.x + playerWidth / 2;

	if (fromPlayerToTop < topBound)
		camera->MoveUp(topBound - fromPlayerToTop);
	else if (fromPlayerToBottom < bottomBound)
		camera->MoveDown(bottomBound - fromPlayerToBottom);

	if (fromPlayerToLeft < leftBound)
		camera->MoveLeft(leftBound - fromPlayerToLeft);
	else if (fromPlayerToRight < rightBound)
		camera->MoveRight(rightBound - fromPlayerToRight);

}

void PlayScene::EnvironmentUpdate(double dt)
{

}

void PlayScene::CollisionProcess(double dt)
{
	//Kiểm tra collision với ground.
	for (int i = 0; i < mapStaticObject.size(); ++i)
	{
		//Lấy BoxRect của Player.
		BoundingBox playerBox = player->getBoundingBox();
		//Lấy BoxRect của MapObject.
		BoundingBox objectBox = mapStaticObject[i]->getStaticObjectBoundingBox();

		collisionOut colOut = Collision::getInstance()->SweptAABB(playerBox, objectBox);
	

		//Gọi đến hàm xử lý va chạm của player.
		if (colOut.side != CollisionSide::none)
			player->OnCollision(mapStaticObject[i], &colOut);

	}
}

void PlayScene::ProcessUpdates(double dt)
{
	KeyboardManager* inputInstance = KeyboardManager::getInstance();
	player->Update(dt);
}