#include "PlayScene01.h"

PlayScene01::PlayScene01()
{
	LoadContent();
}

PlayScene01::~PlayScene01()
{

}

void PlayScene01::LoadContent()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	world = new GameMap(world01tile, world01map, world01MapObject, MapName::CHARLES);
	world->SetCamera(camera);
	camera->SetMapProperties(world->getMapHeight(), world->getMapWidth());
	mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.
}

void PlayScene01::Update(double dt)
{
	PlayScene::Update(dt);
}

void PlayScene01::Draw()
{
	PlayScene::Draw();
}

void PlayScene01::ProcessUpdates(double dt)
{
	PlayScene::ProcessUpdates(dt);
}

void PlayScene01::UpdateCameraWithPlayerPos(double dt)
{
	PlayScene::UpdateCameraWithPlayerPos(dt);
}

void PlayScene01::CollisionProcess(double dt)
{
	PlayScene::CollisionProcess(dt);
}

void PlayScene01::EnvironmentUpdate(double dt)
{
	PlayScene::EnvironmentUpdate(dt);
}