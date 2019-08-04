#include "PlayerKickPart.h"



PlayerKickPart::PlayerKickPart() {
	this->tag = Tag::PLAYER_PART;

	this->isCollidable = true;
	this->existInOneFrame = false;

	this->SetPositionToPlayer();
}

PlayerKickPart::~PlayerKickPart() {

}


void PlayerKickPart::SetPositionToPlayer() {
	auto player = Player::getInstance();

	switch (player->GetMoveDirection()) {
		case MoveDirection::LeftToRight: this->pos.x = player->pos.x + 14.5;break;
		case MoveDirection::RightToLeft: this->pos.x = player->pos.x - 14.5;break;
	}
	this->pos.y = player->pos.y - 1;
}

int PlayerKickPart::GetCollisionDamage() {
	return KICK_DAMAGE;
}

void PlayerKickPart::Update(float dt) {
	// chỉ cho phép object này tồn tại trong 1 frame
	if (!this->existInOneFrame) {
		this->existInOneFrame = this->isCollidable = true;
	}
	else {
		this->existInOneFrame = this->isCollidable = false;
		this->DeactivateObjectInGrid();
	}
}

void PlayerKickPart::Render() {
	// Đây là box ảo nên k cân render
}
BoundingBox PlayerKickPart::getBoundingBox() {
	BoundingBox box;
	box.left = this->pos.x - 5.5;
	box.right = box.left + 11;
	box.top = this->pos.y + 3;
	box.bottom = box.top - 6;
	box.vx = box.vy = 0;

	return box;
}

void PlayerKickPart::OnCollision(Object* object, collisionOut* colOut) {
}

bool PlayerKickPart::OnRectCollided(Object* object, CollisionSide side) {
	return false;
}