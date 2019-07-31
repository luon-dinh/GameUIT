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
	wizard->deltaX += abs(wizard->vx);
	wizard->deltaY += abs(wizard->vy);
	//bay cấp độ 1,bay gần
	if (flyMode == 1)
	{
		if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
			wizard->vx = 0.5;
		else
		{
			wizard->vx = -0.5;
		}
		switch (wizard->GetOnAirState())
		{
		case BossWizard::OnAir::Falling:
			wizard->curanimation->curframeindex = 1;
			wizard->vy = -1.5;
			break;
		case BossWizard::OnAir::Jumping:
			wizard->curanimation->curframeindex = 0;
			if (wizard->deltaY >= 60)
			{
				wizard->deltaY = 0;
				wizard->vy = 0;
				wizard->SetOnAirState(BossWizard::OnAir::Falling);
			}
			break;
		default:
			break;
		}
		return;
	}
	//bay cấp độ 2, bay trung bình
	if (flyMode == 2)
	{
		switch (wizard->GetOnAirState())
		{
		case BossWizard::OnAir::Falling:
			wizard->curanimation->curframeindex = 1;
			wizard->vy = -2;
			wizard->vx = 0;
			break;
		case BossWizard::OnAir::Jumping:
			wizard->curanimation->curframeindex = 0;
			if (wizard->deltaY >= maxY)
			{
				wizard->deltaY = 0;
				wizard->vy = 0;
				wizard->SetOnAirState(BossWizard::OnAir::None);
				if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
					wizard->vx = 2;
				else
				{
					wizard->vx = -2;
				}
			}
			break;
		case BossWizard::OnAir::None:
			wizard->curanimation->curframeindex = 0;
			if (wizard->deltaX >= maxX-30)
			{
				wizard->deltaX = 0;
				wizard->SetOnAirState(BossWizard::OnAir::Falling);
			}
			break;
		default:
			break;
		}
		return;
	}
	//bay cấp độ 3, bay cao và xa
	if (flyMode = 3)
	{
		switch (wizard->GetOnAirState())
		{
		case BossWizard::OnAir::Falling:
			wizard->curanimation->curframeindex = 1;
			wizard->vy = -2;
			wizard->vx = 0;
			break;
		case BossWizard::OnAir::Jumping:
			wizard->curanimation->curframeindex = 0;
			if (wizard->deltaY >= maxY)
			{
				wizard->deltaY = 0;
				wizard->vy = 0;
				wizard->SetOnAirState(BossWizard::OnAir::None);
				if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
					wizard->vx = 2;
				else
				{
					wizard->vx = -2;
				}
			}
			break;
		case BossWizard::OnAir::None:
			wizard->curanimation->curframeindex = 0;
			if (wizard->deltaX >= maxX)
			{
				wizard->deltaX = 0;
				wizard->SetOnAirState(BossWizard::OnAir::Falling);
			}
			break;
		default:
			break;
		}
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
