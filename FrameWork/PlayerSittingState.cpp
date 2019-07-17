#include "PlayerSittingState.h"

PlayerSittingState::PlayerSittingState() {
	this->state = State::DUCKING;
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

BoundingBox PlayerSittingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 7;
	box.bottom = player->pos.y - 21;
	box.left = player->pos.x - 12;
	box.right = player->pos.x + 12;
	return box;
}