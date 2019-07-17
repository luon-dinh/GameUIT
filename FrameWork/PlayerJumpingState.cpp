#include "PlayerJumpingState.h"

void PlayerJumpingState::InputHandler() {
	auto player = Player::getInstance();	
	auto keyboard = KeyboardManager::getInstance();

	if (player == NULL || keyboard == NULL)
		return;

	// nhảy và chạy qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
		player->SetVx(PLAYER_NORMAL_SPEED);
	}
	else {
		// nhảy và chạy qua trái
		if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
			player->SetVx(-PLAYER_NORMAL_SPEED);
		}
	}

	 //tạm thời set ground giả lập
	if (player->pos.y < 70 && player->GetOnAirState() == Player::OnAir::Falling) {
		player->pos.y = 70;
		player->ChangeState(State::DUCKING);
		return;
	}

	// nhảy tới khi vận tốc bằng 0 thì AirState là rơi xuống
	if (player->GetOnAirState() == Player::OnAir::Jumping && player->vy <= 0) {
		player->SetVy(0);
	}
}

void PlayerJumpingState::Update(float dt) {
	this->InputHandler();
}

void PlayerJumpingState::OnCollision(Object* object, collisionOut* collision) {
	//auto player = Player::getInstance();
	//auto side = collision->side;

	//if (object->type == Type::GROUND) {
	//	// chạm vào ground trên đầu
	//	if (side == CollisionSide::top) {
	//		player->SetVy(0);
	//	}
	//	else {
	//		// chạm nền dưới
	//		if (side == CollisionSide::bottom && player->GetOnAirState() == Player::OnAir::Falling) {
	//			player->pos.y -= player->vy * collision->collisionTime + object->height / 2;
	//			player->ChangeState(State::STANDING);
	//		}
	//	}
	//}
}

BoundingBox PlayerJumpingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 20;
	box.bottom = player->pos.y - 18;
	box.left = player->pos.x - 11;
	box.right = player->pos.y + 11;
	return box;
}