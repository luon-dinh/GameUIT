#include "PlayerShockingState.h"

PlayerShockingState::PlayerShockingState() {
	this->state = State::SHOCKING;
}

PlayerShockingState::~PlayerShockingState() {

}

void PlayerShockingState::InputHandler() {
}

void PlayerShockingState::Update(float dt) {
	auto player = Player::getInstance();
}

void PlayerShockingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::ENEMY) {
		player->OnCollisionWithEnemy(object);
		return;
	}

	if (object->type == Type::BULLETTYPE) {
		auto castBullet = (Bullet*)object;

		if (castBullet->GetMoveDirection() != player->GetMoveDirection() && !castBullet->CanGetThroughShield() && player->hasShield) {
			return;
		}
		player->OnCollisionWithBullet(castBullet);
	}
}
