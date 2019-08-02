#pragma once
#include "MovingPlatform.h"
class MovingPlatformCircle : public MovingPlatform
{
	//Tốc độ xoay của platform.
	const double platformMovingSpeedByDeg = 1;

	//Độ delay của platform trong mỗi lần xoay.
	const int delayPerMove = 0;

	//Tốc độ (độ dài dịch chuyển) của platform.
	const double platformMoveSpeedMax = 1;

	int delayTick = 0;

	//Góc hiện tại của platform.
	double currentDegree = 0;

public:
	MovingPlatformCircle(int posX, int posY);
	~MovingPlatformCircle();
	void MovePlatform() override;
};