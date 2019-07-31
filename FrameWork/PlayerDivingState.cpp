#include "PlayerDivingState.h"


PlayerDivingState::PlayerDivingState() {
	this->state = State::DIVING;
	this->countAnimationFrame = 6;
}

void PlayerDivingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();

	// khi không nhấn thì chuyển sang trạng thái nổi
	if (!keyboard->isKeyDown(PLAYER_SIT)) {
		player->ChangeState(State::FLOATING);
		player->SetCollisionAffect(TRUE);
		this->countAnimationFrame = 6;
		return;
	}
}

void PlayerDivingState::Update(float dt) {
	auto player = Player::getInstance();

	if (this->countAnimationFrame == 0) {
		player->curanimation = new Animation(PLAYER, 44, 46);
	}
	else {
		this->countAnimationFrame--;
	}
	
	InputHandler();
}

void PlayerDivingState::OnCollision(Object* object, collisionOut* collision) {

}