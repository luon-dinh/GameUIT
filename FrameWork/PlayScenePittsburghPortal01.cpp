﻿#include "PlayScenePittsburghPortal01.h"

PlayScenePittsburghPortal01::PlayScenePittsburghPortal01()
{
	//Khởi tạo các world.
	world = new GameMap(pbPortal01LightPNG, pbPortal01LightTXT, pbPortal01MapObject, MapName::PITTSBURGHPORTAL1LIGHT);
	worldDark = new GameMap(pbPortal01DarkPNG, pbPortal01DarkTXT,pbPortal01MapObject, MapName::PITTSBURGHPORTAL1DARK);

	world->SetCamera(camera);
	worldDark->SetCamera(camera);

	mapStaticObject = world->getStaticObject();
	currentWorld = worldDark;
}

PlayScenePittsburghPortal01::~PlayScenePittsburghPortal01()
{
	if (worldDark != nullptr)
		delete worldDark;
}

void PlayScenePittsburghPortal01::ResetPlayerPosition()
{
	//Reset lại player khi vừa bắt đầu màn chơi.
	Player * player = Player::getInstance();
	player->pos.x = 64; //Ngay cánh cửa.
	player->pos.y = player->height + 10;
	player->ChangeState(State::JUMPING);
	player->SetAirState(Player::OnAir::Falling);
}

void PlayScenePittsburghPortal01::Update(double dt)
{
	PlaySceneWithLight::Update(dt);
	//Test phím bật/tắt đèn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_L))
		TurnOnOffLight();

	//Test phím chuyển màn.
	if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_O) && isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHLIGHT;
	else if (KeyboardManager::getInstance()->getKeyPressedOnce(DIK_O) && !isLightOn)
		ReplaceToThisMap = MapName::PITTSBURGHDARK;
}