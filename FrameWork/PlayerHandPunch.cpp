#include "PlayerHandPunch.h"


PlayerHandPunch* PlayerHandPunch::instance = NULL;

PlayerHandPunch::PlayerHandPunch() {
	this->SetDamage(2);
	this->SetHealth(1000);
	this->tag = Tag::PLAYER_PART;
}

PlayerHandPunch::~PlayerHandPunch() {

}


void PlayerHandPunch::SetPositionToPlayer() {
	auto player = Player::getInstance();

	switch (player->GetMoveDirection()) {
		case MoveDirection::LeftToRight: this->pos.x = player->pos.x + 19.5;
		case MoveDirection::RightToLeft: this->pos.x = player->pos.x - 19.5;
	}

	if (player->state == State::STAND_PUNCH) {
		this->pos.y = player->pos.y + 11;
		return;
	}
	if (player->state == State::DUCKING_PUNCHING) {
		this->pos.y = player->pos.y - 2;
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
		this->SetActive(true);
		return true;
	}
	this->SetActive(false);
	return false;
}

void PlayerHandPunch::Update(float dt) {
	SetPositionToPlayer();
}

void PlayerHandPunch::Render() {
	// nếu không đang active thì không render
	if (this->GetActive() == false) {
		return;
	}

	// chưa có animation nên chưa render được
}
BoundingBox PlayerHandPunch::getBoundingBox() {
	// width: 11;  height: 4
	// x: 19.5
	// ngồi xuống : y - 2
	// đứng: y + 11
	

	BoundingBox box;
	box.left = this->pos.x / 2 - 5.5;
	box.right = box.left + 11;
	box.top = this->pos.y / 2 + 2;
	box.bottom = box.top - 4;

	return box;
}

void PlayerHandPunch::OnCollision(Object* object, collisionOut* colOut) {

}

bool PlayerHandPunch::OnRectCollided(Object* object, CollisionSide side) {
	int a = 1;
	return false;
}