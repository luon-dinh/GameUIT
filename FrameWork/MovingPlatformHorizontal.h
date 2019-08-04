#pragma once
#include "MovingPlatform.h"
class MovingPlatformHorizontal : public MovingPlatform
{
	//Quãng đường mà nó đi theo phương ngang.
	const int travelRoadLength = 100;

	//Tốc độ mà nó đi theo phương ngang.
	const int travelSpeed = 2;

	//Vị trí bắt đầu lúc nào cũng là nằm bên trái.
	int initX;
	int nextX;
public:
	MovingPlatformHorizontal(int posX, int posY);
	~MovingPlatformHorizontal();
	void MovePlatform() override;
};