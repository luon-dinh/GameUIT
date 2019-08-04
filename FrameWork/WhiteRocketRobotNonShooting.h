#pragma once
#include "RedRocketRobotNonShooting.h"

class WhiteRocketRobotNonShooting : public RedRocketRobotNonShooting
{
	void LoadAllAnimation() override
	{
		if (walking != nullptr)
			delete walking;
		walking = new Animation(Tag::WHITEROCKERTER, 0, 3, walkingSpriteDelay);
		if (standing != nullptr)
			delete standing;
		standing = new Animation(Tag::WHITEROCKERTER, 0, 1);
		if (crouching != nullptr)
			delete crouching;
		crouching = new Animation(Tag::WHITEROCKERTER, 3, 4);
		if (shocking != nullptr)
			delete shocking;
		shocking = new Animation(Tag::WHITEROCKERTER, 4, 5);
	}
public:
	WhiteRocketRobotNonShooting(int posX, int posY) : RedRocketRobotNonShooting(posX, posY) 
	{
		LoadAllAnimation();
	};
	~WhiteRocketRobotNonShooting() {};
};