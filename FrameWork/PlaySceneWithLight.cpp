#include "PlaySceneWithLight.h"

PlaySceneWithLight::PlaySceneWithLight()
{

}

PlaySceneWithLight::~PlaySceneWithLight()
{
	if (worldDark != nullptr)
		delete worldDark;
}

void PlaySceneWithLight::Draw()
{
	currentWorld->Draw();
	//Ta render tiếp player.
	player->Render();
	DrawDebugBoxForStaticObjects();
	DrawDebugBoxForPlayer();
}

void PlaySceneWithLight::Update(double dt)
{
	PlayScene::Update(dt);
}

void PlaySceneWithLight::TurnOnOffLight()
{
	if (isLightOn)
		currentWorld = worldDark;
	else
		currentWorld = world;
	isLightOn = !(isLightOn);
}

void PlaySceneWithLight::ProcessUpdates(double dt)
{
	PlayScene::ProcessUpdates(dt);
}

void PlaySceneWithLight::UpdateCameraWithPlayerPos(double dt)
{
	PlayScene::UpdateCameraWithPlayerPos(dt);
}

void PlaySceneWithLight::CollisionProcess(double dt)
{
	PlayScene::CollisionProcess(dt);
}

void PlaySceneWithLight::EnvironmentUpdate(double dt)
{
	PlayScene::EnvironmentUpdate(dt);
}
