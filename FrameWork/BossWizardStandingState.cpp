#include"BossWizardStandingState.h"

BossWizardStandingState::BossWizardStandingState()
{

}
BossWizardStandingState::~BossWizardStandingState()
{

}

void BossWizardStandingState::InputHandler()
{

}

void BossWizardStandingState::Update(float dt)
{

	auto wizard = BossWizard::getInstance();
	auto player = Player::getInstance();
	float deltaPlayer = abs(player->pos.x - wizard->pos.x);
	if (wizard->flyTimes > 0)
	{
		wizard->flyMode = rand() % 3 + 2;
		wizard->ChangeState(State::FLYING);
		wizard->flyTimes--;
		return;
	}

	if (deltaPlayer > 0)
		wizard->direction = BossWizard::MoveDirection::RightToLeft;
	else
	{
		wizard->direction = BossWizard::MoveDirection::LeftToRight;
	}
	if (wizard->flyMode != 1)
	{
		wizard->flyMode = 1;
		wizard->ChangeState(State::FLYING);
		return;
	}
	else
	{
		wizard->ChangeState(State::RUNNING);
	}

	/*if (deltaPlayer >= wizard->xRun)
	{
		wizard->ChangeState(State::RUNNING);
	}
	else
	{
		if (deltaPlayer < wizard->xPunch&&player->GetOnAirState()==BossWizard::OnAir::None)
		{
			wizard->ChangeState(State::STAND_PUNCH);
		}
		else
		{
			wizard->flyMode = 1;
			wizard->ChangeState(State::FLYING);
		}
	}*/
}
