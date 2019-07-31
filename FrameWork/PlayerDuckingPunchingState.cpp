#include "PlayerDuckingPunchingState.h"

PlayerDuckingPunchingState::PlayerDuckingPunchingState() {
	this->state = State::DUCKING_PUNCHING;
}

void PlayerDuckingPunchingState::InputHandler() {
	auto player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	int timePunching = 0;
	if (player == NULL || keyboard == NULL)
		return;

	// khi đang ngồi nhưng phím đánh đang được giữ
	if (!keyboard->getKeyPressedOnce(PLAYER_ATTACK, timePunching)) {
		if (timePunching < 0 || timePunching >= MAX_PUNCH_TIME)
			player->ChangeState(State::DUCKING);
	}
}

void PlayerDuckingPunchingState::Update(float dt) {
	this->InputHandler();
}

void PlayerDuckingPunchingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;
	if (object->type == Type::ENEMY) {
		player->OnCollisionWithEnemy(object);
		return;
	}

	if (object->type == Type::BULLETTYPE) {
		auto castBullet = (Bullet*)object;
		if (player->hasShield) {
			if ((player->GetMoveDirection() == Object::MoveDirection::LeftToRight && side == CollisionSide::right) || (player->GetMoveDirection() == Object::MoveDirection::RightToLeft && side == CollisionSide::left) && !castBullet->CanGetThroughShield()) {
				return;
			}
		}
		player->OnCollisionWithBullet(castBullet);
	}
}
