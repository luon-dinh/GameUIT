#include"BossWizardPunchingState.h"

BossWizardPunchingState::BossWizardPunchingState()
{

}
BossWizardPunchingState::~BossWizardPunchingState()
{

}

void BossWizardPunchingState::InputHandler()
{

}

void BossWizardPunchingState::Update(float dt)
{
	auto wizard = BossWizard::getInstance();
	auto player = Player::getInstance();
	float deltaPlayer = abs(player->pos.x - wizard->pos.x);
	if (deltaPlayer >= 100)
		wizard->ChangeState(State::RUNNING);
	else
	{
		if (deltaPlayer < 30)
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
