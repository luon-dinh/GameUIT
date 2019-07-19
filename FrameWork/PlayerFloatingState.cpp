#include "PlayerFloatingState.h"

PlayerFloatingState::PlayerFloatingState() {
	this->state = State::FLOATING;
}

void PlayerFloatingState::InputHandler() {

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