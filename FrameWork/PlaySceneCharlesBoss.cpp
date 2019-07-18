#include "PlaySceneCharlesBoss.h"


PlaySceneCharlesBoss::PlaySceneCharlesBoss()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	//Chúng ta tạo ra 2 GameMap : Một sáng một tối dùng để chuyển khi bật đèn sáng/tối.
	world = new GameMap(world01BossTileLight, world01BossMapLight, world01BossMapObject, MapName::CHARLESBOSSLIGHT);
	worldDark = new GameMap(world01BossTileDark, world01BossMapDark, world01BossMapObject, MapName::CHARLESBOSSDARK);

	world->SetCamera(camera);
	worldDark->SetCamera(camera);

	mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.

	currentWorld = world;
	isLightOn = true;
}

PlaySceneCharlesBoss::~PlaySceneCharlesBoss()
{
	if (worldDark != nullptr)
		delete worldDark;
}