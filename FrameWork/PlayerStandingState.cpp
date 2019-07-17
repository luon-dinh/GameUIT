#include"PlayerStandingState.h"
#include "Debug.h"

PlayerStandingState::PlayerStandingState()
{
	state = STANDING;
}

void PlayerStandingState::Update(float dt)
{
	this->InputHandler();
}

void PlayerStandingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();

	if (player == NULL || keyboard == NULL)
		return;

	// di chuyển qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		player->ChangeState(State::RUNNING);
		return;
	}
	// di chuyển qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		player->ChangeState(State::RUNNING);
		return;
	}
	// nhảy lên
	if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		return;	
	}
	// ngồi xuống
	if (keyboard->isKeyDown(PLAYER_SIT)) {
		player->ChangeState(State::DUCKING);
		return;
	}
}

void PlayerStandingState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;
	auto player = Player::getInstance();
	
	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::bottom && player->onAirState != Player::OnAir::None) {
			player->SetAirState(Player::OnAir::None);
		}
	}
}


BoundingBox PlayerStandingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 24;
	box.bottom = player->pos.y - 21;
	box.left = player->pos.x - 11;
	box.right = player->pos.x + 11;
	return box;
}