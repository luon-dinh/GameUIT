#include "BulletRedRocket.h"

BulletRedRocket::BulletRedRocket(MoveDirection rocketDirection, int posX, int posY, int _rocketSpeed)
{
	
	//Nếu hướng đi của tên lửa là từ phải qua thì ta phải chỉnh lại tốc độ của nó.
	if (rocketDirection == MoveDirection::RightToLeft)
		_rocketSpeed *= (-1);
	isExploded = false;

	this->animation = rocketAnim;
	this->direction = rocketDirection;
	rocketSpeed = _rocketSpeed;
	this->pos.x = posX;
	this->pos.y = posY;
	this->vx = rocketSpeed;
	this->vy = 0;
}

BulletRedRocket::~BulletRedRocket()
{
	if (rocketAnim != nullptr)
		delete rocketAnim;
}

void BulletRedRocket::Update(float dt)
{
	if (isExploded)
	{
		UpdateOnExploded(dt);
		return;
	}
	this->animation->Update(dt);
}

BoundingBox BulletRedRocket::getBoundingBox()
{
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	box.left = this->pos.x - 8;
	box.right = this->pos.x;
	if (this->direction == MoveDirection::LeftToRight)
	{
		box.right = this->pos.x + 8;
	}

	else if (this->direction == MoveDirection::RightToLeft)
	{
		box.left = this->pos.x;
	}

	box.top = this->pos.y + 8;
	box.bottom = this->pos.y;
	return box;
}

void BulletRedRocket::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->tag)
	{
	case Tag::PLAYER:
	case Tag::STATICOBJECT:
		this->animation = animationExplode;
		this->vx = this->vy = 0;
		isExploded = true;
		curDelayTime = 0;
		break;
	case Tag::SHIELD:
		break;
	default:
		break;
	}
}