#include "PlayScene01Boss.h"


PlayScene01Boss::PlayScene01Boss()
{
	LoadContent();
}

PlayScene01Boss::~PlayScene01Boss()
{

}

void PlayScene01Boss::Update(double dt)
{
	PlayScene::Update(dt);
}

void PlayScene01Boss::LoadContent()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	world = new GameMap(world01BossMap, world01BossTile, world01BossMapObject, MapName::CHARLESBOSS);
	world->SetCamera(camera);
	camera->SetMapProperties(world->getMapHeight(), world->getMapWidth());
	mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.
}

void PlayScene01Boss::Draw()
{
	PlayScene::Draw();
}

void PlayScene01Boss::ProcessUpdates(double dt)
{
	PlayScene::ProcessUpdates(dt);
}

void PlayScene01Boss::UpdateCameraWithPlayerPos(double dt)
{
	PlayScene::UpdateCameraWithPlayerPos(dt);
}

void PlayScene01Boss::CollisionProcess(double dt)
{
	PlayScene::CollisionProcess(dt);
}

void PlayScene01Boss::EnvironmentUpdate(double dt)
{
	PlayScene::EnvironmentUpdate(dt);
}