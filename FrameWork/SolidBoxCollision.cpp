#include "SolidBoxCollision.h"

SolidBoxCollision::SolidBoxCollision() {

}

SolidBoxCollision::SolidBoxCollision(Object* solidBox, CollisionSide side) {
	SetSolidBox(solidBox);
	SetCollisionSide(side);
}

SolidBoxCollision::~SolidBoxCollision() {

}

Object* SolidBoxCollision::GetSolidBox() {
	return this != NULL ? this->solidBox : NULL;
}

CollisionSide SolidBoxCollision::GetCollisionSide() {
	return this != NULL ? this->side : CollisionSide::none;
}


void SolidBoxCollision::SetCollisionSide(CollisionSide side) {
	if (this != NULL)
		this->side = side;
}

void SolidBoxCollision::SetSolidBox(Object* solidBox) {
	if (this != NULL)
		this->solidBox = solidBox;
}