#include "GroundCollision.h"

GroundCollision::GroundCollision() {

}

GroundCollision::GroundCollision(Object* ground, CollisionSide side) {
	SetGround(ground);
	SetCollisionSide(side);
}

GroundCollision::~GroundCollision() {

}

Object* GroundCollision::GetGround() {
	return this != NULL ? this->ground : NULL;
}

CollisionSide GroundCollision::GetCollisionSide() {
	return this != NULL ? this->side : CollisionSide::none;
}

void GroundCollision::SetCollisionSide(CollisionSide side) {
	if (this != NULL)
		this->side = side;
}

void GroundCollision::SetGround(Object* ground) {
	if (this != NULL)
		this->ground = ground;
}