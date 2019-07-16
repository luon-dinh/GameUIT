#include "PlayerJumpingState.h"


void PlayerJumpingState::InputHandler() {
	auto player = Player::getInstance();	
	auto keyboard = KeyboardManager::getInstance();

	if (player == NULL || keyboard == NULL)
		return;

	// nhảy và chạy qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
		player->SetVx(PLAYER_NORMAL_SPEED);
		return;
	}
	// nhảy và chạy qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetVx(-PLAYER_NORMAL_SPEED);
		return;
	}
	// nhảy tới max tầm
	if (player->pos.y >= PLAYER_MAX_JUMPING_HEIGHT) {
		player->SetAirState(Player::OnAir::Falling);
		return;
	}
}

void PlayerJumpingState::Update(float dt) {
	this->InputHandler();
	Player::getInstance()->curanimation->Update(dt);
}

void PlayerJumpingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND) {
		// chạm vào ground trên đầu
		if (side == CollisionSide::top) {
			player->SetVy(0);
			player->ChangeState(State::FALLING);
		}
	}
}