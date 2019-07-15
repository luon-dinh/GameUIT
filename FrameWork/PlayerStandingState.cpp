#include"PlayerStandingState.h"

PlayerStandingState::PlayerStandingState()
{
	//Player::getInstance()->state = standing;
	state = STANDING;
}

void PlayerStandingState::Update(float dt)
{
	this->InputHandler();
}

void PlayerStandingState::InputHandler()
{
	if (KeyboardManager::getInstance()->isKeyDown(DIK_UP))
	{
		Player::getInstance()->pos.y++;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_DOWN))
	{
		Player::getInstance()->ChangeState(State::RUNNING);
		Player::getInstance()->pos.y--;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_LEFT))
	{
		Player::getInstance()->pos.x--;
	}
	if (KeyboardManager::getInstance()->isKeyDown(DIK_RIGHT))
	{
		Player::getInstance()->pos.x++;
	}
}