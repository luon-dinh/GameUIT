#include "PlayerShieldUpState.h"

PlayerShieldUpState::PlayerShieldUpState() {
	this->state = State::SHIELD_UP;
}

PlayerShieldUpState::~PlayerShieldUpState() {

}

void PlayerShieldUpState::InputHandler() {

}

void PlayerShieldUpState::Update(float dt) {
	InputHandler();
}

void PlayerShieldUpState::OnCollision(Object* object, collisionOut* collision) {

}