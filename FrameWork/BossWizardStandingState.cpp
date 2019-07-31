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
	if (deltaPlayer >= wizard->xRun)
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
	}
}
