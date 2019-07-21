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

	if (!keyboard->isKeyDown(PLAYER_SHIELD_UP)) {
		player->ChangeState(State::STANDING);
		return;
	}
	if (keyboard->isKeyDown(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		return;
	}
}

void PlayerShieldDownState::Downdate(float dt) {
	InputHandler();
	Shield *shield = Shield::getInstance();
	shield->setFrameIndex(2);
	shield->pos.y = Player::getInstance()->getBoundingBox().top - 2;
	shield->pos.x = Player::getInstance()->pos.x;
}

void PlayerShieldDownState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND && side == CollisionSide::bottom) {
		player->SetGroundCollision(new GroundCollision(object, side));
		player->ChangeState(State::STANDING);
		player->pos.y = object->pos.y + player->getHeight() / 2;
	}
}

BoundingBox PlayerShieldDownState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 8;
	box.bottom = player->pos.y - 19;
	box.left = player->pos.x - 10;
	box.right = player->pos.x + 11;
	return box;
}