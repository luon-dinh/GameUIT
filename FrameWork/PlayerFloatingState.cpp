#include "PlayerFloatingState.h"

PlayerFloatingState::PlayerFloatingState() {
	this->state = State::FLOATING;
}

void PlayerFloatingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();


	// bơi qua trái (cùng chiều dòng nước)
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->Float(Player::MoveDirection::RightToLeft);
		// nhấn phím nhảy thì nhảy lên bờ
		if (keyboard->isKeyDown(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
		}
		return;
	}
	else {
		// bơi qua phải
		if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
			player->Float(Player::MoveDirection::LeftToRight);
			if (keyboard->isKeyDown(PLAYER_JUMP)) {
				player->ChangeState(State::JUMPING);
			}
			return;
		}
	}
	if (keyboard->isKeyDown(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		return;
	}

	player->vx = -WATER_SPEED;
}

void PlayerFloatingState::Update(float dt) {
	InputHandler();
}

void PlayerFloatingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;
	
	// đang ở trạng thái rơi từ trên mặt đất xuống nước
	if (object->type == Type::GROUND) {

	}
}

BoundingBox PlayerFloatingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 13;
	box.bottom = player->pos.y - 12;
	box.left = player->pos.x - 18;
	box.right = player->pos.x + 14;
	return box;
}