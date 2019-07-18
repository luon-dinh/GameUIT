#include "PlayScene01Boss.h"


PlayScene01Boss::PlayScene01Boss()
{
	LoadContent();
	currentWorld = world;
}

PlayScene01Boss::~PlayScene01Boss()
{
	if (worldDark != nullptr)
		delete worldDark;
}

void PlayScene01Boss::Update(double dt)
{
	PlayScene::Update(dt);
}

void PlayScene01Boss::LoadContent()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	//Chúng ta tạo ra 2 GameMap : Một sáng một tối dùng để chuyển khi bật đèn sáng/tối.
	world = new GameMap( world01BossTileLight,  world01BossMapLight, world01BossMapObject, MapName::CHARLESBOSSLIGHT);
	worldDark = new GameMap(world01BossTileDark, world01BossMapDark, world01BossMapObject, MapName::CHARLESBOSSDARK);

	world->SetCamera(camera);
	worldDark->SetCamera(camera);

	mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.
}

void PlayScene01Boss::TurnOnOffLight()
{
	//Đảo trạng thái của biến kiểm tra đèn bật.
	isLightOn = !(isLightOn);
}

void PlayScene01Boss::Draw()
{
	currentWorld->Draw();
	
	//Xong xuôi thì ta vẽ player.
	player->Render();
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