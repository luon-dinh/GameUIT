#include "PlayerShieldDownState.h"
#include"Shield.h"

PlayerShieldDownState::PlayerShieldDownState() {
	this->state = State::SHIELD_DOWN;
}

PlayerShieldDownState::~PlayerShieldDownState() {

}

void PlayerShieldDownState::InputHandler() {
	auto keyboard = KeyboardManager::getInstance();
	auto player = Player::getInstance();

	if (!keyboard->isKeyDown(PLAYER_SIT)) {
		if(player->GetOnAirState() == Player::OnAir::None)
			player->ChangeState(State::STANDING);
		else 
		{
			player->ChangeState(State::JUMPING);
		}
		return;
	}
	/*if (keyboard->isKeyDown(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		return;
	}*/
}

void PlayerShieldDownState::Update(float dt) {
	InputHandler();


}

void PlayerShieldDownState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND && side == CollisionSide::bottom) {
   		player->SetOnAirState(Player::OnAir::None);
		player->SetVx(0);
		player->SetStandingGround(object);
		player->pos.y = object->getStaticObjectBoundingBox().top + player->getHeight() / 2;
	}

	if (object->type == Type::WATERRL) {
		player->OnCollisionWithWater(object, collision);
		return;
	}

	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
		return;
	}

	if (object->type == Type::ENEMY) {
		// lúc này đang gây sát thương
		if (side == CollisionSide::bottom) {
			return;
		}
		player->OnCollisionWithEnemy(object);
		return;
	}

	if (object->type == Type::BULLETTYPE) {
		player->OnCollisionWithBullet((Bullet*)object);
		return;
	}
}
