#include "PlayerHandPunch.h"


PlayerHandPunch::PlayerHandPunch() {

	this->tag = Tag::PLAYER_PART;

	// cập nhật vị trí của tay đấm so với player
	this->SetPositionToPlayer();

	this->isCollidable = true;
	this->existInOneFrame = false;
}

PlayerHandPunch::~PlayerHandPunch() {

}

int PlayerHandPunch::GetCollisionDamage() {
	return HAND_PUNCH_DAMAGE;
}

void PlayerHandPunch::SetPositionToPlayer() {
	auto player = Player::getInstance();

	switch (player->GetMoveDirection()) {
	case MoveDirection::LeftToRight:
		this->pos.x = player->pos.x + 14.5;
		break;
	case MoveDirection::RightToLeft:
		this->pos.x = player->pos.x - 14.5;
		break;
	}

	if (player->state == State::STAND_PUNCH) {
		this->pos.y = player->pos.y + 11;
		return;
	}
	if (player->state == State::DUCKING_PUNCHING) {
		this->pos.y = player->pos.y + 6;
	}
}


void PlayerHandPunch::Update(float dt) {
	// chỉ cho phép object này tồn tại trong 1 frame
	if (!this->existInOneFrame) {
		this->existInOneFrame = this->isCollidable = true;
	}
	else {
		this->existInOneFrame = this->isCollidable = false;
		this->DeactivateObjectInGrid();
	}
}

void PlayerHandPunch::Render() {
	// Đây là box ảo nên không cần render
}
BoundingBox PlayerHandPunch::getBoundingBox() {
	BoundingBox box;
	box.left = this->pos.x - 4.5;
	box.right = box.left + 9;
	box.top = this->pos.y + 3;
	box.bottom = box.top - 6;

	return box;
}

void PlayerHandPunch::OnCollision(Object* object, collisionOut* colOut) {

}

bool PlayerHandPunch::OnRectCollided(Object* object, CollisionSide side) {
	return false;
}