#include "PlayerShieldUpState.h"
#include"Shield.h"

PlayerShieldUpState::PlayerShieldUpState() {
	this->state = State::SHIELD_DOWN;
}

PlayerShieldUpState::~PlayerShieldUpState() {

}

void PlayerShieldUpState::InputHandler() {
	auto keyboard = KeyboardManager::getInstance();
	auto player = Player::getInstance();

	if (!keyboard->isKeyDown(PLAYER_SHIELD_UP)) {
		player->ChangeState(State::STANDING);
		return;
	}
	if (keyboard->isKeyDown(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		return;
	}
}

void PlayerShieldUpState::Update(float dt) {
	InputHandler();
	Shield *shield=Shield::getInstance();


}

void PlayerShieldUpState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::BULLETTYPE) {
		auto castBullet = (Bullet*)object;

		if (side == CollisionSide::top && !castBullet->CanGetThroughShield()) {
			return;
		}
		player->OnCollisionWithBullet(castBullet);
		return;
	}

	if (object->type == Type::ENEMY) {
		player->OnCollisionWithEnemy(object);
	}
}
