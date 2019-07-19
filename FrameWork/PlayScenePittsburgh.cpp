﻿#include "PlayScenePittsburgh.h"

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

void PlayScenePittsburgh::ResetPlayerPosition()
{
	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 0;
	//player->pos.y = world->getMapHeight() - 50;
	player->pos.y = SCREEN_HEIGHT;
	player->ChangeState(State::JUMPING);
	player->SetAirState(Player::OnAir::Falling);
}

void PlayScenePittsburgh::Update(double dt)
{
	PlaySceneWithLight::Update(dt);

	//Test phím bật/tắt đèn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_L))
		TurnOnOffLight();

	//Kiểm tra xem player đã đi đến đích chưa.
	if (player->pos.x >= world->getMapWidth() - 50)
		Done = true;
}