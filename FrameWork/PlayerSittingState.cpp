#include "PlayerSittingState.h"

PlayerSittingState::PlayerSittingState() {
	this->state = State::SITTING;
}

PlayerSittingState::~PlayerSittingState() {

}

void PlayerSittingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();

	if (player == NULL || keyboard == NULL)
		return;
	
	// không ở trạng thái ngồi
	if (!keyboard->isKeyDown(PLAYER_SIT)) {
		player->ChangeState(State::STANDING);
		return;
	}
	else {
		// Đổi sang trạng thái nổi trên nước
		if (keyboard->isKeyDown(PLAYER_JUMP)) {
			//player->ChangeState(State::FLOATING);
			return;
		}
	}
	// khi nhấn phím qua trái, ưu tiên qua đi qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		player->ChangeState(State::RUNNING);
		return;
	}

	// khi nhấn phím qua phải, ưu tiên đi qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
		player->SetVx(PLAYER_NORMAL_SPEED);
		player->ChangeState(State::RUNNING);
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		return;
	}
}

void PlayerSittingState::Update(float dt) {
	InputHandler();
}

void PlayerSittingState::OnCollision(Object* object, collisionOut* collision) {

}