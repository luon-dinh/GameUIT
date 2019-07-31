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
	if (wizard->direction == BossWizard::MoveDirection::LeftToRight)
		wizard->vx = 2 * ENEMY_SPEED;
	else
	{
		wizard->vx = -2 * ENEMY_SPEED;
	}
	float deltaPlayer = abs(player->pos.x - wizard->pos.x);
	wizard->deltaX += abs(wizard->vx);
	if (wizard->deltaX >= maxX)
	{
		wizard->vx = 0;
		wizard->deltaX = 0;
		wizard->ChangeState(State::ATTACK);
	}
}