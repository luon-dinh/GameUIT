#include "PlayerFlyingBeatenState.h"


PlayerFlyingBeatenState::PlayerFlyingBeatenState() {
	this->state = State::BEATEN;
	//this->currentFrame = 0;
}

void PlayerFlyingBeatenState::InputHandler() {
}

void PlayerFlyingBeatenState::Update(float dt) {
}

void PlayerFlyingBeatenState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND) {
		if (side == CollisionSide::bottom) {
			player->OnStandingOnGround(object);
			return;
		}
	}


	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
		return;
	}
}