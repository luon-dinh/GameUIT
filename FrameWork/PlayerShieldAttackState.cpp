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
	if (countFrame < MAX_FRAME_PREPARE_ATTACK -1) {
		player->curanimation->curframeindex = 0;
		auto direction = player->GetMoveDirection();
		BoundingBox box = player->getBoundingBox();
		shield->pos.y = box.top - 4;
		switch (direction)
		{
		case Object::LeftToRight:
			shield->pos.x = box.left + 2;
			break;
		case Object::RightToLeft:
			shield->pos.x = box.right - 2;
			break;
		default:
			break;
		}
	}
	else {
		// lúc quăng shield
		player->curanimation->curframeindex = 1;
		auto direction = player->GetMoveDirection();
		BoundingBox box = player->getBoundingBox();
		shield->pos.y = player->pos.y;
		switch (direction)
		{
		case Object::LeftToRight:
			shield->pos.x = box.left;
			break;
		case Object::RightToLeft:
			shield->pos.x = box.right;
			break;
		default:
			break;
		}
		shield->SetShieldState(Shield::ShieldState::Attack);
	}

	countFrame++;

	InputHandler();
}

void PlayerShieldAttackState::OnCollision(Object* object, collisionOut* collision) {

}