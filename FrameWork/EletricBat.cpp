#include "EletricBat.h"


EletricBat::EletricBat(D3DXVECTOR2 pos) : EvilBat(pos){
	this->tag = Tag::EVIL_BAT;
	this->pos = this->initialPos = pos;
	SetXWidth(50, 50);
	SetYHeight(20);

	this->isFlyDown = true;
	this->moveFlag = this->preMoveFlag = 0;		// Not moving flag

	LoadAllAnimations();
	this->ResetGameProperty();

	this->ChangeState(BatState::BelowGround);
	this->damageEffect = DamageEffect::Eletric;
}


EletricBat::~EletricBat() {

}

void EletricBat::LoadAllAnimations() {
	EvilBat::LoadAllAnimations();

	this->animations[BatState::Fly] = new Animation(Tag::EVIL_BAT, 2, 4);
}

bool EletricBat::IsWakenUpBy(Object* object) {
	float distance = sqrt(pow(this->pos.x - object->pos.x, 2) + pow(this->pos.y - object->pos.y, 2));

	if (this->isWakenUp)
		return true;
	// đăt flag isWakenUp bằng true
	this->isWakenUp = distance <= WAKEN_UP_DISTANCE;
	return this->isWakenUp;
}

void EletricBat::StopMoving() {
	// nếu ngừng di chuyển thì chuyển sang trạng thái đậu dưới ground
	this->ChangeState(BatState::BelowGround);
}

bool EletricBat::IsInImmortalState() {
	return (this->turnAroundCount < 2);
}

bool EletricBat::IsFlyAgain() {
	return true;
}

bool EletricBat::OnRectCollided(Object* object, CollisionSide side) {
	if (this->IsInImmortalState()) {
		return false;
	}
	return EvilBat::OnRectCollided(object, side);
}