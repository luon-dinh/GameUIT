#include "PlayerClimbingState.h"


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