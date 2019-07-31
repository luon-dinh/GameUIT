#include "PlayerDyingState.h"


PlayerDyingState::PlayerDyingState() {
	this->state = State::DEAD;
	this->currentFrame = 0;
}

void PlayerDyingState::InputHandler() {
}

void PlayerDyingState::Update(float dt) {
	auto player = Player::getInstance();
	InputHandler();

	this->currentFrame++;
	if (this->currentFrame > ANIMATION_FRAME) {
		this->currentFrame = 0;
		player->ChangeState(State::STANDING);
	}
}

void PlayerDyingState::OnCollision(Object* object, collisionOut* collision) {
}