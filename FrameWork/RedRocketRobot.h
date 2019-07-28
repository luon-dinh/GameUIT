#pragma once
#include "BulletRedRocket.h"
#include "Enemy.h"

class RedRocketRobot : public Enemy
{
public:
	enum RedRocketRobotType
	{
		ONESIDED,
		TWOSIDED,
		NONSHOOTING
	};
private:
	//Delay cho animation đi bộ.
	const int walkingSpriteDelay = 300;

	//Animation.
	Animation* walking;
	Animation* standing;
	Animation* crouching;
	Animation* shocking;

	RedRocketRobotType robotType;
	Player * player;

	//State.
	State robotState;

	void LoadAllAnimation();
public:
	RedRocketRobot(RedRocketRobotType robotType, int posX, int posY);
	~RedRocketRobot();
};