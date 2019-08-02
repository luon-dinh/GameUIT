#include "MovingPlatformHorizontal.h"

MovingPlatformHorizontal::MovingPlatformHorizontal(int posX, int posY) : MovingPlatform(posX, posY)
{
	initX = posX;
	nextX = posX + travelRoadLength;
	this->vx = travelSpeed;
}

MovingPlatformHorizontal::~MovingPlatformHorizontal()
{

}

void MovingPlatformHorizontal::MovePlatform()
{
	if (this->pos.x > nextX || this->pos.x < initX)
		this->vx *= (-1);
	this->pos.x += this->vx;
}