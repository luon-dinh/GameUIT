#include "MovingPlatform.h"
#include "Camera.h"	
#include "KeyboardManager.h"

MovingPlatform::MovingPlatform(int posX, int posY)
{
	fireDownLeft = new PlatformFire(PlatformFire::PlatformFireDirection::TOPTOBOTTOM, this->pos.x - platformWidth / 5,this->pos.y - platformHeight / 2 - 5);
	fireDownRight = new PlatformFire(PlatformFire::PlatformFireDirection::TOPTOBOTTOM, this->pos.x + platformWidth / 5, this->pos.y - platformHeight / 2 - 5);
	fireLeft = new PlatformFire(PlatformFire::PlatformFireDirection::RIGHTTOLEFT, this->pos.x - platformWidth / 2 - 5, this->pos.y);
	fireRight = new PlatformFire(PlatformFire::PlatformFireDirection::LEFTTORIGHT, this->pos.x + platformWidth / 2 + 5, this->pos.y);

	platformAnim = new Animation(Tag::MOVING_PLATFORM, 0, 1, 10000);

	this->pos.x = posX;
	this->pos.y = posY;
	this->vx = this->vy = 0;
}

MovingPlatform::~MovingPlatform()
{
	if (fireDownLeft != nullptr)
		delete fireDownLeft;
	if (fireDownRight != nullptr)
		delete fireDownRight;
	if (fireLeft != nullptr)
		delete fireLeft;
	if (fireRight != nullptr)
		delete fireRight;
	if (platformAnim != nullptr)
		delete platformAnim;
}

void MovingPlatform::Update(float dt)
{
	//Platform đang di chuyển sang hướng bên trái.
	if (this->vx < 0)
	{
		fireRight->Update(dt);
	}
	//Platform đang di chuyển theo hướng bên phải.
	else if (this->vx > 0)
	{
		fireLeft->Update(dt);
	}
	//Platform đang di chuyển theo hướng đi lên.
	if (this->vy > 0)
	{
		fireDownLeft->Update(dt);
		fireDownRight->Update(dt);
	}
	MovePlatform();
}

void MovingPlatform::Render()
{
	//Nếu đang di chuyển qua trái thì render lửa bên phải và ngược lại.
	if (this->vx < 0)
		fireRight->Render();
	else if (this->vx > 0)
		fireLeft->Render();
	if (this->vy > 0)
	{
		fireDownLeft->Render();
		fireDownRight->Render();
	}
	D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));
	platformAnim->Render(viewPort);
}

void MovingPlatform::UpdatePlatformFirePosition()
{
	fireDownLeft->SetFirePosition(this->pos.x - platformWidth / 5, this->pos.y - platformHeight / 2 - 5);
	fireDownRight->SetFirePosition(this->pos.x + platformWidth / 5, this->pos.y - platformHeight / 2 - 5);
	fireLeft->SetFirePosition(this->pos.x - platformWidth / 2 - 5, this->pos.y);
	fireRight->SetFirePosition(this->pos.x + platformWidth / 2 + 5, this->pos.y);
}

//BoundingBox MovingPlatform::getBoundingBox()
//{
//
//}