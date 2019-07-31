#include "PlayerDashingState.h"


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
	
	//if (object->type == Type::SOLIDBOX) {
	//	player->OnCollisionWithSolidBox(object, collision);
	//	player->ChangeState(State::STANDING);
	//	this->curDashTime = 0;
	//}

	this->curDashTime = 0;
	// collide with ground
	player->ChangeState(State::STANDING);
	switch (collision->side)
	{
	case CollisionSide::left:
		player->pos.x = object->getBoundingBox().right + player->getWidth() / 2 + 4;
		break;
	case CollisionSide::right:
		player->pos.x = object->getBoundingBox().left - player->getWidth() / 2 - 4;
		break;
	default:
		break;
	}
}