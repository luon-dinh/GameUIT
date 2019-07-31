#include "PlayerBeatenState.h"


PlayerBeatenState::PlayerBeatenState() {
	this->state = State::BEATEN;
	this->currentFrame = 0;
}

void PlayerBeatenState::InputHandler() {
}

void PlayerBeatenState::Update(float dt) {
	InputHandler();
	auto player = Player::getInstance();
	
	// nếu chết thì chuyển sang trạng thái Dead
	if (player->IsDead()) {
		player->ChangeState(State::DEAD);
		this->currentFrame = 0;
	}
	
	this->currentFrame++;
	if (this->currentFrame > ANIMATION_FRAME) {
		this->currentFrame = 0;
		player->ChangeState(State::STANDING);
	}
}

void PlayerBeatenState::OnCollision(Object* object, collisionOut* collision) {
}