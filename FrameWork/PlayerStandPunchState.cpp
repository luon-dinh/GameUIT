#include"PlayerStandPunchState.h"
#include "Debug.h"

PlayerStandPunchState::PlayerStandPunchState()
{
	state = STAND_PUNCH;
}

void PlayerStandPunchState::Update(float dt)
{
	this->InputHandler();
}

void PlayerStandPunchState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	int timePunching = 0;

	if (player == NULL || keyboard == NULL)
		return;

	if (!keyboard->getKeyPressedOnce(PLAYER_ATTACK, timePunching)) {
		if (timePunching < 0 || timePunching >= MAX_PUNCH_TIME)
			player->ChangeState(State::STANDING);
	}
}

void PlayerStandPunchState::OnCollision(Object* object, collisionOut* collision) {
}
