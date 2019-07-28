#include"Object.h"

BoundingBox Object::getBoundingBox()
{
	BoundingBox box;
	box.top=this->pos.y+this->getHeight()/2;
	box.left = this->pos.x-this->getWidth()/2;
	box.right = box.left + this->getWidth();
	box.bottom = box.top - this->getHeight();
	box.vx = this->vx;
	box.vy = this->vy;
	return box;
}

BoundingBox Object::getStaticObjectBoundingBox()
{
	BoundingBox box;
	box.top = this->pos.y + this->height / 2;
	box.left = this->pos.x - this->width / 2;
	box.bottom = box.top - this->height;
	box.right = box.left + this->width;
	box.vx = box.vy = 0;
	return box;
}

void Object::Render()
{
	
}

void Object::Update(float dt)
{

}

void Object::SetActive(BOOL value) {
	this->isActive = value;
}

BOOL Object::GetActive() {
	return this->isActive;
}


float Object::getWidth()
{
	return SpriteManager::getInstance()->getSprite(this->tag)->getRECT().right - SpriteManager::getInstance()->getSprite(this->tag)->getRECT().left;
}

float Object::getHeight()
{
	auto rect = SpriteManager::getInstance()->getSprite(this->tag)->getRECT();
	auto height =  rect.top - rect.bottom;

	return height;
}

Object::MoveDirection Object::GetMoveDirection() {
	return this->direction;
}

void Object::SetMoveDirection(MoveDirection moveDir) {
	if (this->direction == moveDir)
		return;
	this->direction = moveDir;

	this->vx *= -1;
}

void Object::SetVx(float vx) {
	this->vx = vx;
	if (vx == 0)
		return;
	if (this->direction == MoveDirection::LeftToRight) {
		if (vx < 0) {
			this->direction = MoveDirection::RightToLeft;
		}
	}
	else {
		if (vx > 0) {
			this->direction = MoveDirection::LeftToRight;
		}
	}
}
void Object::SetVy(float vy) {
	this->vy = vy;
	if (this->vy <= 0) {
		// Nếu vận tốc <= 0 khi đang ở trạng thái nhảy thì rơi xuống lại
		if (this->onAirState == OnAir::Jumping || this->onAirState == OnAir::JumpFromWater)
			SetOnAirState(OnAir::Falling);
	}
}
void Object::SetVelocity(D3DXVECTOR2 velocity) {
	SetVx(velocity.x);
	SetVy(velocity.y);
}
void Object::SetAccelerate(D3DXVECTOR2 accelerator) {
	this->accelerator = accelerator;

}

void Object::UpdatePosition() {
	this->SetVx(this->vx + this->accelerator.x);
	this->SetVy(this->vy + this->accelerator.y);

	this->pos.x += this->vx;
	this->pos.y += this->vy;
}


void Object::SetMoveProperty(MoveProperties moveProp) {
	this->moveProperty = moveProp;
}

Object::OnAir Object::GetOnAirState() {
	return this->onAirState;
}

Object::OnAir Object::GetPreOnAirState() {
	return this->preOnAirState;
}

void Object::SetOnAirState(Object::OnAir onAirState) {
	if (this->onAirState == onAirState)
		return;
	this->preOnAirState = this->onAirState;
	this->onAirState = onAirState;
}

bool Object::IsOnGround() {
	return this->currentGround->type == Type::GROUND;
}



Object* Object::GetStandingGround() {
	return this->currentGround;
}

bool Object::IsStopBySolidBox() {
	if (this->moveProperty != MoveProperties::StoppedBySolidBox)
		return false;
	return this->IsStopLeft() || this->IsStopRight();
}

bool Object::IsStopLeft() {
	return this->smashLeft && this->vx <= 0;
}

bool Object::IsStopRight() {
	return this->smashRight && this->vx >= 0;
}

void Object::SetStandingGround(Object* ground) {
	if (ground == NULL) {
		this->currentGround = NULL;
		return;
	}
	if (ground->type == Type::GROUND || ground->type == Type::SOLIDBOX) {
		this->currentGround = ground;
	}
}


void Object::OnFallingOffGround() {
	if (this->GetOnAirState() == OnAir::None) {
		if (this->IsOnGround()) {
			this->SetOnAirState(OnAir::Falling);
		}
		this->ChangeState(State::JUMPING);
		this->SetStandingGround(NULL);
	}
}
void Object::OnStandingOnGround(Object* ground) {
	this->SetStandingGround(ground);
	this->ChangeState(State::STANDING);
	this->pos.y = ground->getBoundingBox().top + this->getHeight() / 2 -2;
}

void Object::OnCollisionWithSolidBox(Object* solidBox, collisionOut* colOut) {
	this->collidedSolidBox = solidBox;
	auto bound = solidBox->getStaticObjectBoundingBox();
	switch (colOut->side) {
	case CollisionSide::left:	OnSmashSolidBox(solidBox, CollisionSide::left); break;
	case CollisionSide::right:	OnSmashSolidBox(solidBox, CollisionSide::right);break;
	case CollisionSide::top: {
		this->SetVy(0);
		this->pos.y = bound.bottom - this->getHeight() / 2 - 2;
		break;
	}
	case CollisionSide::bottom: {
		if (this->GetOnAirState() == OnAir::Falling) {
			OnStandingOnGround(solidBox);
		}
		break;
	}
	}
}
void Object::OnCollisionWithWater(Object* water, collisionOut* colOut) {
	this->ChangeState(State::FLOATING);
	auto objBox = water->getStaticObjectBoundingBox();
	this->pos.y = water->pos.y / 2 + this->getHeight() / 2;
	this->SetStandingGround(NULL);
}
void Object::OnSmashSolidBox(Object* object, CollisionSide side) {
	if ((side == CollisionSide::left) || (side == CollisionSide::right))
		this->SetVx(0);
	//this->collidedSolidBox = object;

	auto bound = object->getStaticObjectBoundingBox();
	switch (side) {
		case CollisionSide::left: {
			this->pos.x = bound.right + this->getWidth() / 2 + 2;
			this->smashLeft = true;
			this->smashRight = false;
			break;
		}
		case CollisionSide::right: {
			this->pos.x = bound.left - this->getWidth() / 2 - 2;
			this->smashRight = true;
			this->smashLeft = false;
		}
	}
}
void Object::OnHeadOnSolidBox(Object* solid) {
	this->SetVy(0);
}