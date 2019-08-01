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
	if (wizard->curanimation->curframeindex == wizard->curanimation->toframe-1)
	{
		if (wizard->turnOffLight&&wizard->flyMode != 1)
		{
			wizard->flyMode = 1;
			wizard->ChangeState(State::FLYING);
			wizard->turnOffLight = false;
			return;
		}
		auto player = Player::getInstance();
		float deltaPlayer = wizard->pos.x - player->pos.x;
		if (deltaPlayer > 0)
			wizard->direction = BossWizard::MoveDirection::RightToLeft;
		else
		{
			wizard->direction = BossWizard::MoveDirection::LeftToRight;
		}
		wizard->ChangeState(State::RUNNING);
	/*	if (wizard->turnOffLight&&wizard->flyMode != 1)
		{
			wizard->flyMode = 1;
			wizard->turnOffLight = false;
			wizard->ChangeState(State::STANDING);
		}*/
	}
	
}
