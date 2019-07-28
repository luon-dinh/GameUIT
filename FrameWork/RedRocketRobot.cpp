#include "RedRocketRobot.h"

RedRocketRobot::RedRocketRobot(RedRocketRobotType _robotType, int posX, int posY)
{
	player = Player::getInstance();

	//Gán giá trị.
	robotType = _robotType;
	this->pos.x = posX;
	this->pos.y = posY;
	robotType = _robotType;
	//Xét toạ độ của player xem nên quay mặt qua hướng nào.
	if (this->pos.x < player->pos.x)
		direction = MoveDirection::LeftToRight;
	else
		direction = MoveDirection::RightToLeft;
	currentAnimation = standing;
}

void RedRocketRobot::LoadAllAnimation()
{
	walking = new Animation(Tag::REDROCKERTER, 0, 3, walkingSpriteDelay);
	standing = new Animation(Tag::REDROCKERTER, 0, 1);
	crouching = new Animation(Tag::REDROCKERTER, 3, 4);
	shocking = new Animation(Tag::REDROCKERTER, 4, 5);
}