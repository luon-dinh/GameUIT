#include"BossWizardStandingState.h"

BossWizardStandingState::BossWizardStandingState()
{
	timeStand = 0;
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
	if (timeStand < maxTimeStand)
	{
		timeStand += dt;
	}
	else
	{
		float deltaPlayer = abs(player->pos.x - wizard->pos.x);

		if (deltaPlayer > 0)
			wizard->direction = BossWizard::MoveDirection::RightToLeft;
		else
		{
			wizard->direction = BossWizard::MoveDirection::LeftToRight;
		}
		if (wizard->flyMode != 1)
		{
			//wizard->flyMode = 1;
			wizard->direction = BossWizard::MoveDirection::LeftToRight;
			wizard->ChangeState(State::STAND_PUNCH);
			return;
		}
		else
		{
			if (wizard->flyTimes > 0)
			{
				wizard->flyMode = rand() % 3 + 2;
				wizard->ChangeState(State::FLYING);
				wizard->flyTimes--;
				return;
			}
			wizard->ChangeState(State::RUNNING);
		}

	}
}
