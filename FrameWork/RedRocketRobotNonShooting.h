#pragma once
#include "RedRocketRobotOneSided.h"

class RedRocketRobotNonShooting : public RedRocketRobotOneSided
{
	const int walkRange = 99999;
public:
	RedRocketRobotNonShooting(int posX, int posY) : RedRocketRobotOneSided(posX, posY)
	{
		//Tính khoảng cách tối đa robot đi được.
		minX = posX - walkRange / 2;
		maxX = posX + walkRange / 2;

		if (direction == MoveDirection::LeftToRight)
			isMovingLeftToRight = true;
		else
			isMovingLeftToRight = false;
		ChangeState(State::WALKING);
	}
	~RedRocketRobotNonShooting() {};
	void OnCollision(Object* object, collisionOut* colOut) override
	{
		if (object->tag == Tag::SHIELD)
		{
			Shield *shield = Shield::getInstance();
			if (shield->state == Shield::ShieldState::Attack)
			{
				//Nếu đang không bị beaten thì mới chuyển trạng thái.
				if (!isBeingBeaten)
				{
					health -= object->GetCollisionDamage();
					ChangeState(State::BEATEN);
				}
			}
		}
		if (object->tag == Tag::STATICOBJECT)
		{
			//Chỉ chuyển sang trạng thái standing khi đang rơi.
			if (object->type == Type::GROUND && robotState == State::FALLING && colOut->side == CollisionSide::bottom)
			{
				ChangeState(State::WALKING);
				this->pos.y -= colOut->collisionTime * vy + (2 * object->height / 3);
			}
		}
	}
};