#pragma once
#include "RedRocketRobotTwoSided.h"
#include "SceneManager.h"
#include "BulletRedRocketNonLinear.h"

class RedRocketRobotTwoSidedNonLinear : public RedRocketRobotTwoSided
{
public:
	RedRocketRobotTwoSidedNonLinear(int posX, int posY) : RedRocketRobotTwoSided(posX, posY) {};
	~RedRocketRobotTwoSidedNonLinear() {};
protected:
	void Fire() override
	{
		if (robotState == State::DUCKING)
			SceneManager::getInstance()->AddObjectToCurrentScene(new BulletRedRocketNonLinear(direction, this->pos.x, this->pos.y, rocketSpeed));
		else
			SceneManager::getInstance()->AddObjectToCurrentScene(new BulletRedRocketNonLinear(direction, this->pos.x, this->pos.y + 15, rocketSpeed));
	}
};