#include "RedRocketRobot.h"

RedRocketRobot::RedRocketRobot(int posX, int posY)
{
	this->tag = Tag::REDROCKERTER;
	player = Player::getInstance();
	this->LoadAllAnimation();
	//Gán giá trị.
	this->pos.x = posX;
	this->pos.y = posY;
	//Xét toạ độ của player xem nên quay mặt qua hướng nào.
	if (this->pos.x < player->pos.x)
		direction = MoveDirection::LeftToRight;
	else
		direction = MoveDirection::RightToLeft;
	currentAnimation = standing;
	health = RedRocketRobotHealth;
}

RedRocketRobot::~RedRocketRobot()
{
	if (walking != nullptr)
		delete walking;
	if (standing != nullptr)
		 standing;
	if (crouching != nullptr)
		delete crouching;
	if (shocking != nullptr)
		delete shocking;
}

void RedRocketRobot::LoadAllAnimation()
{
	walking = new Animation(Tag::REDROCKERTER, 0, 3, walkingSpriteDelay);
	standing = new Animation(Tag::REDROCKERTER, 0, 1);
	crouching = new Animation(Tag::REDROCKERTER, 3, 4);
	shocking = new Animation(Tag::REDROCKERTER, 4, 5);
}

void RedRocketRobot::KillObject()
{
	this->vx = 0;
	this->vy = 0;
	this->health = 0;
	ChangeState(State::BEATEN);
}