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
		wizard->currentanimation->curframeindex = 1;
		wizard->vy = -wizard->flySpeedy;
		if (wizard->flyMode != 1)
			wizard->vx = 0;
		break;
	case BossWizard::OnAir::Jumping:
		if(wizard->flyMode!=1)
			wizard->vx = 0;
		wizard->vy = wizard->flySpeedy;
		wizard->currentanimation->curframeindex = 0;
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
		wizard->currentanimation->curframeindex = 2;
		if (wizard->turnOffLight)
		{
			if (abs(wizard->pos.x - 70) < 5)
			{
				wizard->SetOnAirState(BossWizard::OnAir::Falling);
				return;
			}

		}
		if (wizard->canShootOnAir)
		{
			wizard->timeDelayShootOnAir += dt;
		}
		if (wizard->timeDelayShootOnAir > 40)
		{
			auto scene = SceneManager::getInstance();
			auto bullet = new BulletWizardSpecial();
			bullet->vx = 0;
			bullet->vy = ENEMY_BULLET_SPEED * -3;
			bullet->animation = bullet->animation3;
			if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
				bullet->pos.x = wizard->pos.x + wizard->width / 2;
			else
			{
				bullet->pos.x = wizard->pos.x - wizard->width / 2;
			}
			bullet->pos.y = wizard->pos.y - wizard->height / 2;
			scene->AddObjectToCurrentScene(bullet);
			wizard->timeDelayShootOnAir = 0;
			wizard->canShootOnAir = false;
			return;
		}
		if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
		{
			wizard->vx = wizard->flySpeedx2;
			if (abs(wizard->pos.x + wizard->width/2 - player->pos.x) < 1.5)
			{
				wizard->canShootOnAir = true;
			}
		}
		else
		{
			wizard->vx = -wizard->flySpeedx2;
			if (abs(wizard->pos.x - wizard->width / 2 - player->pos.x) < 1.5)
			{
				wizard->canShootOnAir = true;
			}
		}
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
