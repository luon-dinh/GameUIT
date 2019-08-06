#include "PlayerHandOnRope.h"


PlayerHandOnRope::PlayerHandOnRope() {

	this->tag = Tag::PLAYER_HANG;

	// cập nhật vị trí của tay đấm so với player
	this->SetPositionToPlayer();
	this->isCollidable = true;
}

PlayerHandOnRope::~PlayerHandOnRope() {

}

void PlayerHandOnRope::SetPositionToPlayer() {
 	auto player = Player::getInstance();

	switch (player->GetMoveDirection()) {
	case MoveDirection::LeftToRight:
		this->pos.x = player->pos.x + 3;
		break;
	case MoveDirection::RightToLeft:
		this->pos.x = player->pos.x - 3;
		break;
	}
	
	this->pos.y = player->pos.y + 23;

}


void PlayerHandOnRope::Update(float dt) {
	if (!this->isCollidable) {
		return;
 	}
	SetPositionToPlayer();
}

void PlayerHandOnRope::Render() {
	// Đây là box ảo nên không cần render
}

BoundingBox PlayerHandOnRope::getBoundingBox() {
	auto player = Player::getInstance();
	BoundingBox box;
	box.left = this->pos.x - 3;
	box.right = box.left + 6;
	box.top = this->pos.y + 5.5;
	box.bottom = box.top - 11;
	box.vx = box.vy = 0;
	return box;
}

void PlayerHandOnRope::OnCollision(Object* object, collisionOut* colOut) {

}

bool PlayerHandOnRope::OnRectCollided(Object* object, CollisionSide side) {
	auto player = Player::getInstance();

	// nếu tay va chạm với dây
	if (object->type == Type::ROPE) {
		auto player = Player::getInstance();
		player->OnClimbingTheRope(object);
		this->DeactivateObjectInGrid();
		this->isCollidable = false;
		return true;
	}
	return false;
}

void PlayerHandOnRope::OnNotCollision(Object* object) {
}