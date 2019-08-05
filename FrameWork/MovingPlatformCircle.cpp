#include "MovingPlatformCircle.h"

MovingPlatformCircle::MovingPlatformCircle(int posX, int posY) : MovingPlatform(posX, posY)
{

}

MovingPlatformCircle::~MovingPlatformCircle()
{

}

void MovingPlatformCircle::MovePlatform()
{
	if (delayTick < delayPerMove)
	{
		++delayTick;
		return;
	}
	delayTick = 0;
	currentDegree += platformMovingSpeedByDeg;
	if (currentDegree >= 360)
		currentDegree -= 360;
	this->vx = cos(currentDegree * PI / 180) * platformMoveSpeedMax;
	this->vy = -sin(currentDegree * PI / 180) * platformMoveSpeedMax;
	this->pos.x += this->vx;
	this->pos.y += this->vy;
}