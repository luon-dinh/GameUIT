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
		timeStand += wizard->defaultDT;
	}
	else
	{
		timeStand = 0;
		float deltaPlayer = abs(player->pos.x - wizard->pos.x);

		if (deltaPlayer > 0)
			wizard->direction = BossWizard::MoveDirection::RightToLeft;
		else
		{
			wizard->direction = BossWizard::MoveDirection::LeftToRight;
		}
		//đang đứng gần onoff thì punch
		if (wizard->flyMode != 1&&wizard->GetStandingGround()->type==Type::GROUND)
		{
			//wizard->flyMode = 1;
			wizard->direction = BossWizard::MoveDirection::LeftToRight;
			wizard->ChangeState(State::STAND_PUNCH);
			return;
		}
		else
		{
			//wizard->ChangeState(State::RUNNING);
			if (wizard->countBullet <= 3)
				wizard->ChangeState(State::ATTACK);
			else
			{
				wizard->countBullet = 0;
				wizard->ChangeState(State::RUNNING);
			}
		}

	}
}
