#include "PlayerClimbingState.h"


PlayerClimbingState::PlayerClimbingState() {
	this->state = State::CLIMBING;
	this->currentFrame = 0;
}

void PlayerClimbingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();

	if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
		player->pos.y += 10;
		player->ChangeState(State::JUMPING);
		this->currentFrame = 0;
		return;
	}
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		player->SetMoveDirection(Object::MoveDirection::LeftToRight);
		return;
	}
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		player->SetMoveDirection(Object::MoveDirection::RightToLeft);
		return;
	}
	if (keyboard->isKeyDown(PLAYER_SIT))
	{
		player->SetOnAirState(Player::OnAir::Falling);
		player->ChangeState(State::JUMPING);
		player->pos.y -= 2;
		return;
	}
}

void PlayerClimbingState::Update(float dt) {
	InputHandler();

	//auto player = Player::getInstance();
	//if (this->currentFrame == FRAME_PER_ANIMATION) {
	//	if (++player->curanimation->curframeindex == NUMBER_OF_ANIMATION) {
	//		player->curanimation->curframeindex = 0;
	//	}
	//	this->currentFrame = 0;
	//}
	//this->currentFrame++;
}

void PlayerClimbingState::OnCollision(Object* object, collisionOut* collision) {
}