#include "PlayScenePittsburgh.h"

PlayScenePittsburgh::PlayScenePittsburgh()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	//Chúng ta tạo ra 2 GameMap : Một sáng một tối dùng để chuyển khi bật đèn sáng/tối.
	world = new GameMap(world02TileLightPNG, world02LightTXT, world02MapObject, MapName::PITTSBURGHLIGHT);
	worldDark = new GameMap(world02TileDarkPNG, world02DarkTXT, world02MapObject, MapName::PITTSBURGHDARK);

	world->SetCamera(camera);
	worldDark->SetCamera(camera);

	mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.
	currentWorld = worldDark;
}

PlayScenePittsburgh::~PlayScenePittsburgh()
{
	if (worldDark != nullptr)
		delete worldDark;
}

void PlayScenePittsburgh::Update(double dt)
{
	PlaySceneWithLight::Update(dt);
	if (player->pos.x >= world->getMapWidth() - 50)
		Done = true;
}