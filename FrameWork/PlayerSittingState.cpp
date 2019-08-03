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
		// Đổi sang trạng thái nhảy xuống nước
		if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
			// nếu ở trên main ground thì rơi xuống nước
			if (player->IsOnGround()) {
				player->SetOnAirState(Player::OnAir::Falling);
			}
			player->ChangeState(State::JUMPING);
			return;
		} 
	}

	// khi nhấn phím qua trái, ưu tiên qua đi qua trái
	if (keyboard->getKeyPressedOnce(PLAYER_MOVE_LEFT)) {
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		player->ChangeState(State::RUNNING);
		return;
	}

	// khi nhấn phím qua phải, ưu tiên đi qua phải
	if (keyboard->getKeyPressedOnce(PLAYER_MOVE_RIGHT)) {
		player->ChangeState(State::RUNNING);
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		return;
	}

	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		player->ChangeState(State::DUCKING_PUNCHING);
	}
}

void PlayerSittingState::Update(float dt) {
	InputHandler();
}

void PlayerSittingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::ENEMY) {
		player->OnCollisionWithEnemy(object);
		return;
	}

	if (object->type == Type::BULLETTYPE) {
		auto castBullet = (Bullet*)object;

		if (castBullet->GetMoveDirection() != player->GetMoveDirection() && !castBullet->CanGetThroughShield() && player->hasShield){
			return;
		}
		player->OnCollisionWithBullet(castBullet);
	}
}
