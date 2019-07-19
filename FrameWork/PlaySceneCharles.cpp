#include "PlaySceneCharles.h"

PlaySceneCharles::PlaySceneCharles()
{
	//Các singleton đã được tự động load khi gọi hàm khởi tạo tại class cha.
	//Vì vậy chúng ta không cần thực hiện lại việc load singleton.

	world = new GameMap(world01tile, world01map, world01MapObject, MapName::CHARLES);
	world->SetCamera(camera);
	camera->SetMapProperties(world->getMapHeight(), world->getMapWidth());
	mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.
}

PlaySceneCharles::~PlaySceneCharles()
{

}

void PlaySceneCharles::ResetPlayerPosition()
{
	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 100;
	player->pos.y = SCREEN_HEIGHT;
	player->ChangeState(State::JUMPING);
	player->SetAirState(Player::OnAir::Falling);
}

void PlaySceneCharles::Update(double dt)
{
	PlayScene::Update(dt);
	//Xét thêm điều kiện hoàn thành là khi player đi đến tận cùng phải của map.
	if (player->pos.x >= world->getMapWidth() - 100)
		Done = true;
}