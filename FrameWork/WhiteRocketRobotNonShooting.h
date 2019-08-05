#pragma once
#include "RedRocketRobotNonShooting.h"

class WhiteRocketRobotNonShooting : public RedRocketRobotNonShooting
{
	void LoadAllAnimation() override
	{
		if (walking != nullptr)
			walking = new Animation(Tag::WHITEROCKERTER, 0, 3, walkingSpriteDelay);
		if (standing != nullptr)
			standing = new Animation(Tag::WHITEROCKERTER, 0, 1);
		if (crouching != nullptr)
			crouching = new Animation(Tag::WHITEROCKERTER, 3, 4);
		if (shocking != nullptr)
			shocking = new Animation(Tag::WHITEROCKERTER, 4, 5);
	}
public:
	WhiteRocketRobotNonShooting(int posX, int posY) : RedRocketRobotNonShooting(posX, posY) 
	{
		LoadAllAnimation();
	};
	~WhiteRocketRobotNonShooting() {};
};