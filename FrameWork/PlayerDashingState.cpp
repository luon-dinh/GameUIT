#include "PlayerDashingState.h"

BoundingBox PlayerDashingState::getBoundingBox() {
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 8;
	box.bottom = player->pos.y - 21;
	if (player->direction == Player::MoveDirection::RightToLeft)
	{
		box.left = player->pos.x - 19;
		box.right = player->pos.x ;
	}
	else if (player->direction == Player::MoveDirection::LeftToRight)
	{
		box.left = player->pos.x;
		box.right = player->pos.x + 19;
	}
	//box.left = player->pos.x - 11;
	//box.right = player->pos.x + 11;
	return box;
}

PlayerDashingState::PlayerDashingState() {
	this->state = State::DASHING;
	this->curDashTime = 0;
}

void PlayerDashingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	

	// chuyển sang trạng thái nhảy
	if (keyboard->isKeyDown(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		this->curDashTime = 0;
		return;
	}

	// chuyển sang trạng thái ngồi
	if (keyboard->isKeyDown(PLAYER_SIT)) {
		player->ChangeState(State::DUCKING);
		this->curDashTime = 0;
		return;
	}
	
	// chuyển về trạng thái đứng
	if (this->curDashTime > MAX_DASHING_TIME) {
		player->ChangeState(State::STANDING);
		this->curDashTime = 0;
		return;
	}

	this->curDashTime += 13;
}

void PlayerDashingState::Update(float dt) {
	InputHandler();
}

void PlayerDashingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	
	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
		player->ChangeState(State::STANDING);
		this->curDashTime = 0;
	}
}