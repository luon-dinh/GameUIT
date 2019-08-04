#include "PlayScenePittsburghBoss.h"

PlayScenePittsburghBoss::PlayScenePittsburghBoss()
{
	world = new GameMap(pittsburghBossPNG, pittsburghBossTXT, nullptr, MapName::PITTSBURGHBOSS);
	world->SetCamera(camera);
	grid = new Grid(world->getMapWidth(), world->getMapHeight(), pittsburghBossSpawn, pittsburghBossMapObject);
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
	player->pos.x = 30;
	player->pos.y = SCREEN_HEIGHT - 50;
	player->ChangeState(State::JUMPING);
	player->SetOnAirState(Player::OnAir::Falling);

	//Update lại camera sau khi set.
	UpdateCameraWithPlayerPos();
}