#include "PlayScenePittsburghBoss.h"

PlayScenePittsburghBoss::PlayScenePittsburghBoss()
{
	world = new GameMap(pittsburghBossPNG, pittsburghBossTXT, nullptr, MapName::PITTSBURGHBOSS);
}

PlayScenePittsburghBoss::~PlayScenePittsburghBoss()
{

}

void PlayScenePittsburghBoss::GoToNextScene()
{

}

void PlayScenePittsburghBoss::Update(double dt)
{
	PlayScene::Update(dt);
}

void PlayScenePittsburghBoss::ResetPlayerPosition()
{
	//Reset lại player luôn.
	Player * player = Player::getInstance();
	player->pos.x = 0;
	player->pos.y = SCREEN_HEIGHT - 50;
	player->ChangeState(State::JUMPING);
	player->SetOnAirState(Player::OnAir::Falling);

	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}