﻿#include "PlayerShieldAttackState.h"

BoundingBox PlayerShieldAttackState::getBoundingBox() {
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 15;
	box.bottom = player->pos.y - 21;
	box.left = player->pos.x - 11;
	box.right = player->pos.x + 21;
	return box;
}

PlayerShieldAttackState::PlayerShieldAttackState() {
	this->state = State::SHIELD_ATTACK;
	this->countFrame = 0;
}

void PlayerShieldAttackState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();	
	
	if (this->countFrame == MAX_FRAME_PREPARE_ATTACK) {
		player->ChangeState(State::STANDING);
		this->countFrame = 0;
		return;
	}
}

void PlayerShieldAttackState::Update(float dt) {

	auto player = Player::getInstance();

	if (countFrame <= MAX_FRAME_PREPARE_ATTACK / 2) {
		player->curanimation = new Animation(PLAYER, 11, 12);

	}
	else {
		player->curanimation = new Animation(PLAYER, 12, 13);
		player->hasShield = FALSE;
	}

	countFrame++;

	InputHandler();
}

void PlayerShieldAttackState::OnCollision(Object* object, collisionOut* collision) {

}