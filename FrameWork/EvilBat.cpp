#include "EvilBat.h"


EvilBat::EvilBat(D3DXVECTOR2 position) {
	this->pos = this->initialPos = position;
	SetXWidth(200, 150);
	SetYHeight(70);

	this->isFlyDown = true;
	this->moveFlag = this->preMoveFlag = 0;		// Not moving flag
	//this->curentMoveHandler = &this->StopMoving;

	LoadAllAnimations();
	this->activeAnimation = false;

	this->ResetGameProperty();
}

EvilBat::~EvilBat() {
	delete this->explodeAnim;
	delete this->belowGroundAnim;
	delete this->fakeContainerAnim;
	delete this->flyAnim;
}

void EvilBat::SetMoveFlag(bool value) {
	this->preMoveFlag = this->moveFlag;
	this->moveFlag = value;
}

bool EvilBat::IsMoveFlagChanged() {
	return this->moveFlag != this->preMoveFlag;
}

void EvilBat::LoadAllAnimations() {
	this->fakeContainerAnim = new Animation(Tag::EVIL_BAT, 0, 3);
	this->belowGroundAnim = new Animation(Tag::EVIL_BAT, 3, 6);
	this->flyAnim = new Animation(Tag::EVIL_BAT, 6, 8);
	this->explodeAnim = new Animation(Tag::EVIL_BAT, 8, 9);
}

void EvilBat::SetXWidth(int leftDentaX, int rightDentaX) {
	this->leftX = this->pos.x - leftDentaX;
	this->rightX = this->pos.x + rightDentaX;
}

void EvilBat::SetYHeight(int yHeight) {
	this->edgeY = this->pos.y - yHeight;
}

void EvilBat::Update(float dt) {
	// nếu move flag không thay đổi thì không 
	if (this->IsMoveFlagChanged())
		CallMove();
	// Gọi tới handler của hàm chuyển động hiện tại
	(*this.*curentMoveHandler)();
	// Cập nhật vị trí
	this->UpdatePosition();
	// Nếu có animation thì update animation
	if (this->activeAnimation) {
		this->currentAnimation->Update(dt);
	}
}

void EvilBat::Render() {
	if (!isDead)
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		this->currentAnimation->Render(pos);
	}
}

void EvilBat::ChangeState(BatState state) {
	switch (state) {
	case BatState::BelowGround: {
		this->activeAnimation = false;
		this->currentAnimation = belowGroundAnim;
		this->currentAnimation->curframeindex = 0;
		break;
	}
	case BatState::Dead: {
		this->activeAnimation = true;
		this->currentAnimation = explodeAnim;
		this->isCollidable = false;
		break;
	}
	case BatState::OnNeck: {
		this->activeAnimation = false;
		this->currentAnimation = fakeContainerAnim;
		this->currentAnimation->curframeindex = 0;
	}
	case BatState::Fly: {
		this->activeAnimation = true;
		break;
	}
	}
}

void EvilBat::OnCollision(Object* object, collisionOut* colOut) {

}
bool EvilBat::OnRectCollided(Object* object, CollisionSide side) {
	switch (object->tag) {
		case Tag::PLAYER:
		case Tag::SHIELD: {
			if (this->state == BatState::OnNeck) {
				this->ChangeState(BatState::Fly);
			}
			GameObjectProperty::health--;
		}
	}
	return false;
}

void EvilBat::UpdatePosition() {
	this->pos.x += this->vx;
	this->pos.y += this->vy;
}


void EvilBat::CallMove() {
	//if (this->moveFlag == 0) {
	//	this->curentMoveHandler = &StopMoving;
	//	return;
	//}
	//// di chuyển dọc
	//if (this->moveFlag == 1) {
	//	this->curentMoveHandler = &Move1;
	//	return;
	//}
	//// di chuyển ngang
	//if (this->moveFlag == 2) {
	//	this->curentMoveHandler = &Move1;
	//	return;
	//}
	//// di chuyển tròn
	//if (this->moveFlag == 3) {
	//	this->curentMoveHandler = &Move1;
	//	return;
	//}
}

void EvilBat::StopMoving() {
	this->vx = this->vy = 0;
}

void EvilBat::Move1() {
	if (this->pos.y < edgeY && this->turnAroundCount == 0) {
		this->vx = -2;
		this->direction = MoveDirection::RightToLeft;
		this->vy = 0;
		this->moveFlag = 2;
		return;
	}
	if (this->pos.y > this->initialPos.y) {
		SetMoveFlag(2);
		return;
	}
	this->vx = 0;
	// đi xuống
	if (this->isFlyDown)
		this->vy = -2;
	else
		// đi lên
		this->vy = 2;
}

void EvilBat::Move2() {
	if (this->pos.x < this->leftX || this->pos.x > this->rightX) {
		SetMoveFlag(3);
		this->turnAroundCount++;
		// nếu đã quay hơn một nửa số lần quy định thì bay ngược lên lại
		if (this->turnAroundCount > TURN_AROUND_COUNT / 2) {
			this->isFlyDown = false;
			this->vy = 1;
		}
		else {
			this->vy = -1;
		}
		return;
	}
	else {
		// nếu đã đi đủ số vòng
		if (this->turnAroundCount == TURN_AROUND_COUNT) {
			// nếu tọa độ x bằng x ban đầu thì di chuyển ngược lên
			if (this->pos.x == this->initialPos.x) {
				SetMoveFlag(1);
				return;
			}
		}
	}
	if (this->direction == MoveDirection::LeftToRight) {
		this->vx = 2;
	}
	else {
		this->vx = -2;
	}
	this->vy = 0;
}

void EvilBat::Move3() {

	int maxLeftX = this->leftX - TURN_AROUND_POINT_DENTA;
	int maxRightX = this->rightX + TURN_AROUND_POINT_DENTA;

	if (this->pos.x < maxLeftX || this->pos.x > maxRightX) {
		this->vx *= -1;
		if (this->pos.x < maxLeftX)
			this->direction = MoveDirection::LeftToRight;
		else
			this->direction = MoveDirection::RightToLeft;
	}
	else {
		if (this->pos.x < this->leftX || this->pos.x > this->rightX)
			return;
		if ((this->vx > 0 && this->pos.x > this->leftX) || (this->vx < 0 && this->pos.x < this->rightX)) {
			SetMoveFlag(2);
		}
	}
}

int EvilBat::GetDamage() {
	return 2;
}
int EvilBat::GetCollisionDamage() {
	return this->GetDamage();
}

void EvilBat::ResetGameProperty() {
	this->SetHealth(2);
}