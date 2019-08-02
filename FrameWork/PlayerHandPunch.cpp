#include "PlayerHandPunch.h"


PlayerHandPunch* PlayerHandPunch::instance = NULL;

PlayerHandPunch::PlayerHandPunch() {
	this->SetDamage(2);
	this->SetHealth(1000);
	this->tag = Tag::PLAYER_PART;
}

PlayerHandPunch::~PlayerHandPunch() {

}

int PlayerHandPunch::GetCollisionDamage() {
	return 2;
}

void PlayerHandPunch::SetPositionToPlayer() {
	auto player = Player::getInstance();

	switch (player->GetMoveDirection()) {
		case MoveDirection::LeftToRight: 
			this->pos.x = player->pos.x + 11.5;
			break;
		case MoveDirection::RightToLeft: 
			this->pos.x = player->pos.x - 11.5;
			break;
	}

	if (player->state == State::STAND_PUNCH) {
		this->pos.y = player->pos.y + 3;
		return;
	}
	if (player->state == State::DUCKING_PUNCHING) {
		this->pos.y = player->pos.y + 2;
	}
}
PlayerHandPunch* PlayerHandPunch::getInstance() {
	if (instance == NULL) {
		instance = new PlayerHandPunch();
	}
	return instance;
}

void PlayerHandPunch::releaseInstance() {
	delete instance;
}

BOOL PlayerHandPunch::GetActive() {
	auto player = Player::getInstance();

	if (player->state == State::STAND_PUNCH || player->state == State::DUCKING_PUNCHING) {
		this->isCollidable = true;
		return true;
	}
	this->isCollidable = false;
	return false;
}

void PlayerHandPunch::Update(float dt) {
	SetPositionToPlayer();
	GetActive();
}

void PlayerHandPunch::Render() {
	// Đây là box ảo nên không cần render
}
BoundingBox PlayerHandPunch::getBoundingBox() {

	BoundingBox box;
	box.left = this->pos.x + 4;
	box.right = box.left + 15;
	box.top = this->pos.y + 6;
	box.bottom = box.top - 6;

	return box;
}

void PlayerHandPunch::OnCollision(Object* object, collisionOut* colOut) {

}

bool PlayerHandPunch::OnRectCollided(Object* object, CollisionSide side) {
	int a = 1;
	return false;
}