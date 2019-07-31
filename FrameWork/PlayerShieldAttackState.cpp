#include "PlayerShieldAttackState.h"


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
	auto shield = Shield::getInstance();

	// lúc gồng
	if (countFrame <= MAX_FRAME_PREPARE_ATTACK / 2) {
		player->curanimation = animation1;

	}
	else {
		// lúc quăng shield
		player->curanimation = animation2;
		shield->SetShieldState(Shield::ShieldState::Attack);
	}

	countFrame++;

	InputHandler();
}

void PlayerShieldAttackState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::ENEMY) {
		player->OnCollisionWithEnemy(object);
		return;
	}

	if (object->type == Type::BULLETTYPE) {
		player->OnCollisionWithBullet((Bullet*)object);
	}
}