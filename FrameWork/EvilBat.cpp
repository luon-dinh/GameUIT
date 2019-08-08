#include "EvilBat.h"


EvilBat::EvilBat(D3DXVECTOR2 position) {
	this->tag = Tag::EVIL_BAT;
	this->pos = this->initialPos = position;
	SetXWidth(50, 50);
	SetYHeight(20);

	this->isFlyDown = true;
	this->moveFlag = this->preMoveFlag = 0;		// Not moving flag

	LoadAllAnimations();
	this->ResetGameProperty();

	ChangeState(EvilBat::BatState::OnNeck);
}

EvilBat::~EvilBat() {
}

void EvilBat::SetMoveFlag(int value) {
	this->preMoveFlag = this->moveFlag;
	this->moveFlag = value;
}

bool EvilBat::IsMoveFlagChanged() {
	return this->moveFlag != this->preMoveFlag;
}

void EvilBat::LoadAllAnimations() {
	this->animations[BatState::Dead] = new Animation(Tag::ENEMYEXPLODE, 0, 3, 150);
	this->animations[BatState::OnNeck] = new Animation(Tag::EVIL_BAT, 4, 7);
	this->animations[BatState::BelowGround] = new Animation(Tag::EVIL_BAT, 7, 10);
	this->animations[BatState::Fly] = new Animation(Tag::EVIL_BAT, 0, 2);	
}

void EvilBat::SetXWidth(int leftDentaX, int rightDentaX) {
	this->leftX = this->pos.x - leftDentaX;
	this->rightX = this->pos.x + rightDentaX;
}

void EvilBat::SetYHeight(int yHeight) {
	this->edgeY = this->pos.y - yHeight;
}

void EvilBat::Update(float dt) {
	if (!this->isCollidable && this->state != BatState::Dead) {
		if (++this->incollidableFrameCount > INCOLLIDABLE_FRAME) {
			this->incollidableFrameCount = 0;
			this->isCollidable = true;
		}
	}
	else {
		switch (this->state) {
			case BatState::Dead: Explode();break;
			case BatState::Fly: CallMove();break;
			case BatState::BelowGround:
			case BatState::OnNeck: {
				if (this->IsWakenUpBy(Player::getInstance())) {
					// nếu animation chưa được active thì active nó
					if (this->activeAnimation == false) {
						this->activeAnimation = true;
						break;
					}
					else {
						// đã chạy xong animation thì chuyển sang trạng thái chuẩn bị bay
						if (this->currentAnimation->curframeindex == 2) {
							this->PrepareToFly();
						}
					}
				}
				break;
			}
		}
	}
	// cập nhật animation
	if (this->activeAnimation) {
		this->currentAnimation->Update(dt);
	}
	// cập nhật vị trí
	UpdatePosition();
}

void EvilBat::Explode() {
	if (this->currentAnimation->curframeindex == 2) {
		Player::getInstance()->ScoreUp(this->score);
		SoundManager::getinstance()->play(SoundManager::SoundName::object_explode);
		this->DeactivateObjectInGrid();
	}
}

void EvilBat::InnerRender() {
	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	this->currentAnimation->Render(pos);
}

void EvilBat::Render() {
	if (this->isCollidable || this->state == BatState::Dead) {
		InnerRender();
		return;
	}	
	// thời gian flip đã tới
	if (++this->flipFrameCount > FLIP_RENDER_FRAME) {
		this->flipFrameCount = 0;
		InnerRender();
	}
}
void EvilBat::ChangeState(BatState state) {
	this->currentAnimation = this->animations[state];
	this->state = state;
	switch (state) {
		case BatState::BelowGround: {
			this->activeAnimation = false;
			this->currentAnimation->curframeindex = 0;
			this->vx = this->vy = 0;
			this->isWakenUp = false;
			this->isCollidable = true;
			break;
		}
		case BatState::Dead: {
			this->activeAnimation = true;
			this->isCollidable = false;
			this->vx = this->vy = 0;
			GameObjectProperty::health = 0;
			break;
		}
		case BatState::OnNeck: {
			this->activeAnimation = false;
			this->currentAnimation->curframeindex = 0;
			this->prepareFlyCount = -1;
			this->isCollidable = true;
			break;
		}
		case BatState::Fly: {
			this->activeAnimation = true;
			this->currentAnimation->curframeindex = 0;
			this->activeFly = true;
			break;
		}
	}
}

void EvilBat::OnCollision(Object* object, collisionOut* colOut) {

}
bool EvilBat::OnRectCollided(Object* object, CollisionSide side) {
	if (!this->isCollidable) {
		return false;
	}
	if (object->type == Type::SPIKE) {
		this->ChangeState(BatState::Dead);
	}
	switch (object->tag) {
		case Tag::PLAYER:
			OnBeaten(object, object->GetCollisionDamage());
			return true;
		case Tag::SHIELD: {
			auto shield = Shield::getInstance();
			// chỉ xét va chạm với shield khi shield đang attack
			if (shield->state == Shield::ShieldState::Attack) {
				OnBeaten(object, object->GetCollisionDamage());
				return true;
			}
		}
	}
	return false;
}

void EvilBat::UpdatePosition() {
	this->pos.x += this->vx;
	this->pos.y += this->vy;
}


void EvilBat::CallMove() {
	// không di chuyển
	if (this->moveFlag == 0) {
		StopMoving();
		if (!this->activeFly)
			return;
		// nếu đã có thể bay lại thì bay
		if (this->IsFlyAgain()) {
			this->SetMoveFlag(1);
		}
		return;
	}
	// di chuyển dọc
	if (this->moveFlag == 1) {
		Move1();
		return;
	}
	if (this->moveFlag == 5) {
		if (++this->prepareFlyCount > PREPARE_TO_FLY_FRAME) {
			this->prepareFlyCount = 0;
			this->activeAnimation = true;
			this->SetMoveFlag(1);
		}
		return;
	}
	// di chuyển ngang
	if (this->moveFlag == 2) {
		Move2();
		return;
	}
	// di chuyển tròn
	if (this->moveFlag == 3) {
		Move3();
		return;
	}
}

void EvilBat::PrepareToFly() {
	this->ChangeState(BatState::Fly);
	this->vx = this->vy = 0;
	this->SetMoveFlag(5);
	return;
}

void EvilBat::StopMoving() {
	this->vx = this->vy = 0;
}

bool EvilBat::IsWakenUpBy(Object* object) {
	return this->isWakenUp;
}

bool EvilBat::IsFlyAgain() {
	this->movingDelayFrame++;
	if (this->movingDelayFrame > this->MOVING_DELAY_FRAME) {
		this->movingDelayFrame = 0;
		return true;
	}
	return false;
}

void EvilBat::Move1() {

	if (this->pos.y < edgeY && this->turnAroundCount == 0) {
		this->vx = -2;
		this->direction = MoveDirection::RightToLeft;
		this->vy = 0;
		SetMoveFlag(2);
		return;
	}
	if (abs(this->pos.y - this->initialPos.y) <= 2 && this->turnAroundCount == this->TURN_AROUND_COUNT) {
		this->initialPos.y = this->pos.y;
		this->vx = this->vy = 0;
		this->turnAroundCount = 0;
		this->isFlyDown = true;
		SetMoveFlag(0);
		return;
	}
	this->vx = 0;
	// đi xuống
	if (this->isFlyDown)
		this->vy = -1.1;
	else
		// đi lên
		this->vy = 1.1;
}

void EvilBat::Move2() {
	if (this->pos.x < this->leftX || this->pos.x > this->rightX) {
		SetMoveFlag(3);
		this->turnAroundCount++;
		// nếu đã quay hơn một nửa số lần quy định thì bay ngược lên lại
		if (this->turnAroundCount > TURN_AROUND_COUNT / 2) {
			this->isFlyDown = false;
			this->vy = 1.5;
		}
		else {
			this->vy = -1.5;
		}
		return;
	}
	else {
		// nếu đã đi đủ số vòng
		if (this->turnAroundCount == TURN_AROUND_COUNT) {
			// nếu tọa độ x bằng x ban đầu thì di chuyển ngược lên
			if (abs(this->pos.x - this->initialPos.x) <= 2) {
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

void EvilBat::OnBeaten(Object* object, int customDamage = 0) {
	if (this->state == BatState::OnNeck) {
		this->isCollidable = false;
		this->isWakenUp = true;
	}
	if (customDamage <= 0) {
		return;
	}
	GameObjectProperty::health--;
	if (this->IsDead()) {
		this->ChangeState(BatState::Dead);
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