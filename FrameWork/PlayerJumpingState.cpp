#include "PlayerJumpingState.h"


PlayerJumpingState::PlayerJumpingState() {
	this->state = State::JUMPING;
}


void PlayerJumpingState::InputHandler() {
	auto player = Player::getInstance();	
	auto keyboard = KeyboardManager::getInstance();

	if (player == NULL || keyboard == NULL)
		return;


	// nhảy và chạy qua phải
	if (keyboard->getKeyPressedOnce(PLAYER_MOVE_RIGHT)) {
		player->SetVx(PLAYER_NORMAL_SPEED);
	}
	else {
		// nhảy và chạy qua trái
		if (keyboard->getKeyPressedOnce(PLAYER_MOVE_LEFT)) {
			player->SetVx(-PLAYER_NORMAL_SPEED);
		}
	}

	// tạm thời set ground giả lập
	if (player->pos.y <= 100 && player->onAirState == Player::OnAir::Falling) {
		player->pos.y = 100;
		player->SetAirState(Player::OnAir::None);
		player->ChangeState(State::STANDING);
		player->SetVx(0);
		player->SetVy(0);
	}

	// nhảy tới max tầm
	if (player->onAirState == Player::OnAir::Jumping && player->vy <= 0) {
		player->SetAirState(Player::OnAir::Falling);
	}
	

}

void PlayerJumpingState::Update(float dt) {
	this->InputHandler();
	Player::getInstance()->curanimation->Update(dt);
}

void PlayerJumpingState::OnCollision(Object* object, collisionOut* collision) {
	//auto player = Player::getInstance();
	//auto side = collision->side;

	//if (object->type == Type::GROUND) {
	//	// chạm vào ground trên đầu
	//	if (side == CollisionSide::top) {
	//		player->SetVy(0);
	//		player->SetAirState(Player::OnAir::Falling);
	//	}
	//	else {
	//		// chạm nền dưới
	//		if (side == CollisionSide::bottom) {
	//			player->pos.y = object->pos.y + player->getHeight() / 2 + object->height / 2;
	//			player->SetAirState(Player::OnAir::None);
	//			player->ChangeState(State::STANDING);
	//		}
	//	}
	//}
}