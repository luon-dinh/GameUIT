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
	if (deltaPlayer >= 200)
		wizard->ChangeState(State::RUNNING);
	else
	{
		if(deltaPlayer<30)
			wizard->ChangeState(State::STAND_PUNCH);
		else
		{
			wizard->flyMode = 1;
			wizard->ChangeState(State::FLYING);
		}
	}
}
