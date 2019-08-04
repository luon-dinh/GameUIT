#include"BossWizardRunningState.h"

BossWizardRunningState::BossWizardRunningState()
{

}
BossWizardRunningState::~BossWizardRunningState()
{

}

void BossWizardRunningState::InputHandler()
{

}

void BossWizardRunningState::Update(float dt)
{
	auto wizard = BossWizard::getInstance();
	auto player = Player::getInstance();
	if (wizard->pos.x < wizard->minMap || wizard->pos.x > wizard->maxMap)
	{
		if (wizard->pos.x < wizard->minMap)
		{
			wizard->direction = BossWizard::MoveDirection::LeftToRight;
		}
		else
		{
			wizard->direction = BossWizard::MoveDirection::RightToLeft;
		}
	}
	if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
		wizard->vx = runningSpeed;
	else
	{
		wizard->vx = -runningSpeed;
	}
	
	float deltaPlayer = abs(player->pos.x - wizard->pos.x);
	wizard->deltaX += abs(wizard->vx);

	//nếu chạy hết maxX thì bắn
	if (wizard->deltaX >= maxX)
	{
		wizard->vx = 0;
		wizard->deltaX = 0;
		wizard->ChangeState(State::ATTACK);
	}
}