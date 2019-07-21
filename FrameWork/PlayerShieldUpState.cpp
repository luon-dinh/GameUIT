#include "PlayerShieldUpState.h"
#include"Shield.h"

PlayerShieldUpState::PlayerShieldUpState() {
	this->state = State::SHIELD_UP;
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
	shield->setFrameIndex(2);
	shield->pos.y = Player::getInstance()->getBoundingBox().top - 2;
	shield->pos.x = Player::getInstance()->pos.x;

}

void PlayerShieldUpState::OnCollision(Object* object, collisionOut* collision) {

}

BoundingBox PlayerShieldUpState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 22;
	box.bottom = player->pos.y - 21;
	box.left = player->pos.x - 12;
	box.right = player->pos.x + 12;
	return box;
}