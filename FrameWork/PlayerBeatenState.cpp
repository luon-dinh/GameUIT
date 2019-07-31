#include "PlayerBeatenState.h"


PlayerBeatenState::PlayerBeatenState() {
	this->state = State::BEATEN;
	this->currentFrame = 0;
}

void PlayerBeatenState::InputHandler() {
}

void PlayerBeatenState::Update(float dt) {
	auto player = Player::getInstance();
	InputHandler();
	
	this->currentFrame++;
	if (this->currentFrame > ANIMATION_FRAME) {
		this->currentFrame = 0;
		player->ChangeState(State::STANDING);
	}
}

void PlayerBeatenState::OnCollision(Object* object, collisionOut* collision) {
}