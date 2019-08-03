#pragma once
#include "MovingPlatform.h"

class MovingPlatformCrossed : public MovingPlatform
{
	//Vị trí xuất phát lúc nào cũng là ở phía dưới.
	const double platformSpeed = 1;

	//Quãng đường mà nó sẽ đi.
	const int travelRoadLength = 100;

	//Góc mà nó sẽ đi.
	const double travelAngle = 30;

	//Toạ độ ban đầu của Moving Platform (lúc được Spawn).
	int initX;
	int initY;
	int nextX;
	int nextY;
public:
	MovingPlatformCrossed(int posX, int posY);
	~MovingPlatformCrossed();
	void MovePlatform() override;
};