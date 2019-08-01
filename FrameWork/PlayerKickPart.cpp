#include "PlayerKickPart.h"


PlayerKickPart* PlayerKickPart::instance = NULL;

PlayerKickPart::PlayerKickPart() {
	this->SetDamage(2);
	this->SetHealth(1000);
	this->tag = Tag::PLAYER_PART;
}

PlayerKickPart::~PlayerKickPart() {

}


void PlayerKickPart::SetPositionToPlayer() {
	auto player = Player::getInstance();

	switch (player->GetMoveDirection()) {
	case MoveDirection::LeftToRight: this->pos.x = player->pos.x + 19.5;break;
	case MoveDirection::RightToLeft: this->pos.x = player->pos.x - 19.5;break;
	}

	if (player->state == State::STAND_PUNCH) {
		this->pos.y = player->pos.y + 11;
		return;
	}
	if (player->state == State::DUCKING_PUNCHING) {
		this->pos.y = player->pos.y - 2;
	}
}
PlayerKickPart* PlayerKickPart::getInstance() {
	if (instance == NULL) {
		instance = new PlayerKickPart();
	}
	return instance;
}

void PlayerKickPart::releaseInstance() {
	delete instance;
}

BOOL PlayerKickPart::GetActive() {
	auto player = Player::getInstance();

	if (player->state == State::KICKING) {
		this->SetActive(true);
		return true;
	}
	this->SetActive(false);
	return false;
}

void PlayerKickPart::Update(float dt) {
	SetPositionToPlayer();
}

void PlayerKickPart::Render() {
	// nếu không đang active thì không render
	if (this->GetActive() == false) {
		return;
	}

	// chưa có animation nên chưa render được
}
BoundingBox PlayerKickPart::getBoundingBox() {
	BoundingBox box;
	box.left = this->pos.x / 2 - 5.5;
	box.right = box.left + 11;
	box.top = this->pos.y / 2 + 2;
	box.bottom = box.top - 4;

	return box;
}

void PlayerKickPart::OnCollision(Object* object, collisionOut* colOut) {
}

bool PlayerKickPart::OnRectCollided(Object* object, CollisionSide side) {
	int a = 1;
	return false;
}