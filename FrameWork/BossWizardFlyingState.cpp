#include"BossWizardFlyingState.h"
#include"SceneManager.h"
BossWizardFlyingState::BossWizardFlyingState()
{

}
BossWizardFlyingState::~BossWizardFlyingState()
{

}

void BossWizardFlyingState::InputHandler()
{

}

void BossWizardFlyingState::Fly(float dt)
{
	auto wizard = BossWizard::getInstance();
	auto player = Player::getInstance();
	wizard->deltaY += abs(wizard->vy);
	wizard->deltaX += abs(wizard->vx);
	if (wizard->flyMode == 1)
	{
		if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
			wizard->vx = wizard->flySpeedx1;
		else
		{
			wizard->vx = -wizard->flySpeedx1;
		}
	}
	switch (wizard->GetOnAirState())
	{
	case BossWizard::OnAir::Falling:
		wizard->curanimation->curframeindex = 1;
		wizard->vy = -wizard->flySpeedy;
		if (wizard->flyMode != 1)
			wizard->vx = 0;
		break;
	case BossWizard::OnAir::Jumping:
		if(wizard->flyMode!=1)
			wizard->vx = 0;
		wizard->vy = wizard->flySpeedy;
		wizard->curanimation->curframeindex = 0;
		if (wizard->flyMode == 1&& wizard->deltaY >= maxFly1)
		{
			wizard->deltaY = 0;
			wizard->vy = 0;
			wizard->SetOnAirState(BossWizard::OnAir::Falling);
			return;
		}
		else if (wizard->pos.y >mapHeight-wizard->height)
		{
			wizard->vy = 0;
			wizard->SetOnAirState(BossWizard::OnAir::None);
		}
		break;
	case BossWizard::OnAir::None:
		if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
			wizard->vx = wizard->flySpeedx2;
		else
		{
			wizard->vx = -wizard->flySpeedx2;
		}
		wizard->curanimation->curframeindex = 0;
		if (wizard->canShootOnAir)
		{
			wizard->timeDelayShootOnAir += dt;
		}
		if (wizard->timeDelayShootOnAir > 50)
		{
			auto scene = SceneManager::getInstance();
			auto bullet = new BulletWizardSpecial();
			bullet->vy = ENEMY_BULLET_SPEED * -3;
			bullet->animation = bullet->animation3;
			bullet->pos.x = wizard->pos.x;
			bullet->pos.y = wizard->pos.y - wizard->height / 2;
			scene->AddObjectToCurrentScene(bullet);
			wizard->timeDelayShootOnAir = 0;
			wizard->canShootOnAir = false;
		}
		if (abs(wizard->pos.x - player->pos.x) < 1)
		{
			wizard->canShootOnAir = true;
		}
		/*if (wizard->deltaX>mapWidth-wizard->width/2)
		{
			wizard->vx = 0;
			wizard->SetOnAirState(BossWizard::OnAir::Falling);
		}*/
		break;
	default:
		break;
	}
}

void BossWizardFlyingState::Update(float dt)
{
	auto wizard = BossWizard::getInstance();
	if ((wizard->pos.x < 15 || wizard->pos.x>240)&&wizard->deltaX>=5)
	{
		wizard->SetOnAirState(BossWizard::OnAir::Falling);
	}
	Fly(dt);
}
