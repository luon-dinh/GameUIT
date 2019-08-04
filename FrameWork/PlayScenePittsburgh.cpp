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

	//mapStaticObject = world->getStaticObject(); //Lấy entity của tất cả các object có trong map.
	currentWorld = worldDark;
	//Xét tạo Grid.
	grid = new Grid(world->getMapWidth(), world->getMapHeight(), world02Spawn, world02MapObject);
	//Thêm player và shield vào Grid.
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
	player->pos.y = world->getMapHeight() - 50;
	//player->pos.y = SCREEN_HEIGHT;
	player->ChangeState(State::JUMPING);
	player->SetOnAirState(Player::OnAir::Falling);
	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}

void PlayScenePittsburgh::Update(double dt)
{
	PlaySceneWithLight::Update(dt);

	KeyboardManager* kbInstance = KeyboardManager::getInstance();

	//Test phím bật/tắt đèn.
	if (kbInstance->getKeyPressedOnce(DIK_L))
		TurnOnOffLight();

	//Test phím qua màn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_Q))
	{
		Done = true;
		ReplaceToThisMap = MapName::PITTSBURGHBOSS;
	}

	//Test phím chuyển màn.
	if (kbInstance->getKeyPressedOnce(DIK_O) && isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHPORTAL1LIGHT;
	else if (kbInstance->getKeyPressedOnce(DIK_O) && !isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHPORTAL1DARK;

	if (kbInstance->getKeyPressedOnce(DIK_K) && isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHPORTAL2LIGHT;
	else if (kbInstance->getKeyPressedOnce(DIK_K) && !isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHPORTAL2DARK;

	//Kiểm tra xem player đã đi đến đích chưa.
	GoToNextScene();
		
}

void PlayScenePittsburgh::GoToNextScene()
{
	//Xét từng trường hợp để đi đến map tiếp theo.
	//Nếu player đang ở vị trí portal thứ 1.
	if (player->pos.x < 600 && player->pos.x > 550 && player->pos.y > 765 && player->pos.y < 820)
	{
		//Xét xem đèn sáng hay tối để replace cho phù hợp.
		if (isLightOn)
			ReplaceToThisMap = MapName::PITTSBURGHPORTAL1LIGHT;
		else
			ReplaceToThisMap = MapName::PITTSBURGHPORTAL1DARK;
	}
	//Nếu player đang ở vị trí portal thứ 2.
	else if (player->pos.x > 815 && player->pos.x < 850 && player->pos.y > 285 && player->pos.y < 340)
	{
		//Xét xem đèn đang sáng hay tối để replace cho phù hợp.
		if (isLightOn)
			ReplaceToThisMap = MapName::PITTSBURGHPORTAL2LIGHT;
		else
			ReplaceToThisMap = MapName::PITTSBURGHPORTAL2DARK;
	}
	else if (player->pos.x >= world->getMapWidth() - 50 && player->pos.y <= SCREEN_HEIGHT)
	{
		Done = true;
		ReplaceToThisMap = MapName::PITTSBURGHBOSS;
	}
}