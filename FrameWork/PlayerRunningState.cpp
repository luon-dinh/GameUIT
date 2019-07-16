#include "PlayerRunningState.h"



PlayerRunningState::PlayerRunningState()
{
	state = RUNNING;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	if (player == NULL || keyboard == NULL)
		return;

	// đang chạy và nhấn xuống thì không có hiệu ứng gì
	if (keyboard->isKeyDown(PLAYER_SIT))
	{
		return;
	}


	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		if (keyboard->isKeyDown(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
			
		}
		return;
	} 

	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		if (keyboard->isKeyDown(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);

		}
		return;
	}



	// Không phím nào được nhấn thì chuyển sang trạng thái đứng yên
	player->SetVx(0);
	player->ChangeState(State::STANDING);
}

void PlayerRunningState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;

	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::top || side == CollisionSide::bottom) {
			Player::getInstance()->vy = 0;
		}
	}
}

void PlayerRunningState::Update(float dt)
{
	this->InputHandler();
}