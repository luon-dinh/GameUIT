#include "PlayerDashingState.h"

BoundingBox PlayerDashingState::getBoundingBox() {
	return BoundingBox();

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
		return;
	}

	// chuyển sang trạng thái ngồi
	if (keyboard->isKeyDown(PLAYER_SIT)) {
		player->ChangeState(State::DUCKING);
		return;
	}
	
	// chuyển về trạng thái đứng
	if (this->curDashTime > MAX_DASHING_TIME) {
		player->ChangeState(State::STANDING);
		this->curDashTime = 0;
		return;
	}

	this->curDashTime += 40;
}

void PlayerDashingState::Update(float dt) {
}

void PlayerDashingState::OnCollision(Object* object, collisionOut* collision) {

}