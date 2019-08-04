#include "EletricBat.h"


EletricBat::EletricBat(D3DXVECTOR2 pos) : EvilBat(pos) {
	this->ChangeState(BatState::BelowGround);
}


EletricBat::~EletricBat() {

}

void EletricBat::LoadAllAnimations() {
	EvilBat::LoadAllAnimations();

	this->animations[BatState::Fly] = new Animation(Tag::EVIL_BAT, 2, 4);
}