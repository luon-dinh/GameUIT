﻿#include "PlayerDuckingPunchingState.h"

PlayerDuckingPunchingState::PlayerDuckingPunchingState() {
	this->state = State::DUCKING_PUNCHING;
}

void PlayerDuckingPunchingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	if (player == NULL || keyboard == NULL)
		return;

	// khi đang ngồi nhưng phím đánh đang được giữ
	if (!keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		player->ChangeState(State::DUCKING);
	}
}

void PlayerDuckingPunchingState::Update(float dt) {
	this->InputHandler();
}

void PlayerDuckingPunchingState::OnCollision(Object* object, collisionOut* collision) {

}

BoundingBox PlayerDuckingPunchingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 6;
	box.bottom = player->pos.y - 21;
	box.left = player->pos.x - 26;
	box.right = player->pos.y + 12;
	return box;
}