#include "MovingPlatformCrossed.h"

MovingPlatformCrossed::MovingPlatformCrossed(int posX, int posY) : MovingPlatform(posX, posY)
{
	initX = posX;
	initY = posY;
	auto degToRad = [](double deg) {return deg * PI / 180; };
	nextX = sin(degToRad(travelAngle)) * travelRoadLength + initX;
	nextY = cos(degToRad(travelAngle)) * travelRoadLength + initY;
	this->vx = sin(degToRad(travelAngle)) * platformSpeed;
	this->vy = cos(degToRad(travelAngle)) * platformSpeed;
}

MovingPlatformCrossed::~MovingPlatformCrossed()
{
	
}

void MovingPlatformCrossed::MovePlatform()
{
	//Nếu bản thân platform đang trong đoạn từ init tới next ...
	if (initY <= this->pos.y && this->pos.y <= nextY)
	{

	}
	//Đụng nóc trên hoặc dưới thì cho nó đổi hướng.
	else
	{
		this->vy *= (-1);
		this->vx *= (-1);
	}
	this->pos.x += this->vx;
	this->pos.y += this->vy;
}
