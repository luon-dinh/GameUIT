#include "PlayerState.h"

bool PlayerState::detectCollision		= false;
Object* PlayerState::object				= NULL;
CollisionSide PlayerState::side			= CollisionSide::none;

void PlayerState::SetCollisionInfo(Object* object, CollisionSide side) {
	detectCollision = true;
	object = object;
	side = side;
}

bool PlayerState::GetCollisionResult() {
	return detectCollision;
}