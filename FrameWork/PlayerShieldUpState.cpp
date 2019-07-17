#include "PlayerShieldUpState.h"

PlayerShieldUpState::PlayerShieldUpState() {
	this->state = State::SHIELD_UP;
}

PlayerShieldUpState::~PlayerShieldUpState() {

}

void PlayerShieldUpState::InputHandler() {

}

void PlayerShieldUpState::Update(float dt) {
	InputHandler();
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