#include"PlayerStandingState.h"

PlayerStandingState::PlayerStandingState()
{
	Player::getInstance()->vx = 0;
	Player::getInstance()->vy = 0;
	//Player::getInstance()->state = standing;
	state = STANDING;
}

void PlayerStandingState::Update(float dt)
{
	this->InputHandler();
}

void PlayerStandingState::InputHandler()
{
	if (KeyboardManager::getInstance()->isKeyDown(DIK_A)||KeyboardManager::getInstance()->isKeyDown(DIK_D))
	{
		
	}
}