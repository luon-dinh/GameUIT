#include "PlayScenePittsburghPortal01.h"

PlayScenePittsburghPortal01::PlayScenePittsburghPortal01()
{
	//Khởi tạo các world.
	//Tham khảo thêm trong các class khác.
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
}