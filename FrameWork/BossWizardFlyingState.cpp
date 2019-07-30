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
	//bay cấp độ 1,bay gần
	if (flyMode == 1)
	{

		return;
	}
	//bay cấp độ 2, bay trung bình
	if (flyMode == 2)
	{
		auto wizard = BossWizard::getInstance();
		wizard->deltaX += abs(wizard->vx);
		wizard->deltaY += abs(wizard->vy);
		switch (wizard->GetOnAirState())
		{
		case BossWizard::OnAir::Falling:
			wizard->curanimation->curframeindex = 1;
			wizard->vy -= GROUND_GRAVITY;
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
			if (wizard->deltaX >= maxX-50)
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
		auto wizard = BossWizard::getInstance();
		wizard->deltaX += abs(wizard->vx);
		wizard->deltaY += abs(wizard->vy);
		switch (wizard->GetOnAirState())
		{
		case BossWizard::OnAir::Falling:
			wizard->curanimation->curframeindex = 1;
			wizard->vy -= GROUND_GRAVITY;
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
	Fly(wizard->flyMode);
}
