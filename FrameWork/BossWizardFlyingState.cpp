#include"BossWizardFlyingState.h"

BossWizardFlyingState::BossWizardFlyingState()
{

}
BossWizardFlyingState::~BossWizardFlyingState()
{

}

void BossWizardFlyingState::InputHandler()
{

}

void BossWizardFlyingState::Fly(int flyMode)
{
	auto wizard = BossWizard::getInstance();
	wizard->deltaY += abs(wizard->vy);
	wizard->deltaX += abs(wizard->vx);
	if (flyMode == 1)
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
		if (flyMode != 1)
			wizard->vx = 0;
		break;
	case BossWizard::OnAir::Jumping:
		if(flyMode!=1)
			wizard->vx = 0;
		wizard->vy = wizard->flySpeedy;
		wizard->curanimation->curframeindex = 0;
		if (flyMode == 1&& wizard->deltaY >= maxFly1)
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
		if (wizard->deltaX>mapWidth-wizard->height/2)
		{
			wizard->SetOnAirState(BossWizard::OnAir::Falling);
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
	Fly(wizard->flyMode);
}
