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


BoundingBox PlayerStandPunchState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 20;
	box.bottom = player->pos.y - 21;
	if (player->GetMoveDirection() == Player::MoveDirection::RightToLeft)
	{
		box.left = player->pos.x - 18;
		box.right = player->pos.x + 11;	
	}
	else
	{
		box.left = player->pos.x - 11;
		box.right = player->pos.x + 18;
	}
	return box;
}