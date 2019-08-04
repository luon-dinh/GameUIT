#include "PlayerShockingState.h"

PlayerShockingState::PlayerShockingState() {
	this->state = State::SHOCKING;
	this->curShockFrame = 0;
}

PlayerShockingState::~PlayerShockingState() {

}

void PlayerShockingState::InputHandler() {
}

void PlayerShockingState::Update(float dt) {
	auto player = Player::getInstance();

	if (++this->curShockFrame > SHOCKING_FRAME) {
		this->curShockFrame = 0;
		if (player->GetOnAirState() == Object::OnAir::None) {
			player->ChangeState(State::STANDING);
		}
		else {
			player->SetOnAirState(Object::OnAir::Falling);
		}
	}
}

void PlayerShockingState::OnCollision(Object* object, collisionOut* collision) {
}
