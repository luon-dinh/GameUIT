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
	if (wizard->timePunch < wizard->maxTimeToPunch)
		wizard->timePunch += dt;
	else
	{
		wizard->timePunch = 0;
		if (wizard->currentanimation->curframeindex == wizard->currentanimation->toframe - 1)
		{
			// nếu đang tắt đèn thì bay xuống
			if (wizard->turnOffLight&&wizard->flyMode != 1)
			{
				wizard->flyMode = 1;
				wizard->ChangeState(State::FLYING);
				wizard->turnOffLight = false;
				return;
			}
			// ở dưới đất thì chạy
			auto player = Player::getInstance();
			float deltaPlayer = wizard->pos.x - player->pos.x;
			if (deltaPlayer > 0)
				wizard->direction = BossWizard::MoveDirection::RightToLeft;
			else
			{
				wizard->direction = BossWizard::MoveDirection::LeftToRight;
			}
			wizard->ChangeState(State::RUNNING);
		}
	}
}
