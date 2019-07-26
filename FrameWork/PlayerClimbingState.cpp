#include "PlayerClimbingState.h"

BoundingBox PlayerClimbingState::getBoundingBox() {
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 8;
	box.bottom = player->pos.y - 21;
	if (player->GetMoveDirection() == Object::MoveDirection::RightToLeft)
	{
		box.left = player->pos.x - 19;
		box.right = player->pos.x;
	}
	else if (player->GetMoveDirection() == Player::MoveDirection::LeftToRight)
	{
		box.left = player->pos.x;
		box.right = player->pos.x + 19;
	}
	//box.left = player->pos.x - 11;
	//box.right = player->pos.x + 11;
	return box;
}

PlayerClimbingState::PlayerClimbingState() {
	this->state = State::DASHING;
	this->curDashTime = 0;
}

void PlayerClimbingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
}

void PlayerClimbingState::Update(float dt) {
	InputHandler();
}

void PlayerClimbingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();

	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
		player->ChangeState(State::STANDING);
		this->curDashTime = 0;
	}
}