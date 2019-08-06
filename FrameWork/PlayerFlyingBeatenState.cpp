#include "PlayerFlyingBeatenState.h"
#include "SceneManager.h"

PlayerFlyingBeatenState::PlayerFlyingBeatenState() {
	this->state = State::BEATEN;
	//this->currentFrame = 0;
}

void PlayerFlyingBeatenState::InputHandler() {
}

void PlayerFlyingBeatenState::Update(float dt) {
	auto player = Player::getInstance();

	if (player->IsDead()) {
		player->OnFallingOffGround();
	}
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

	if (object->type == Type::ROPE) {
		PlayerHandOnRope* handOnRope = new PlayerHandOnRope();
		SceneManager::getInstance()->AddObjectToCurrentScene(handOnRope);
		return;
	}

	if (object->type == Type::SPIKE) {
		if (side == CollisionSide::bottom){
			if (player->IsNonAttackable()) {
				player->OnStandingOnGround(object);
			}
			else {
				player->OnCollisionWithSpike(object);
			}
			return;
		}
	}
}