#pragma once
#include "RedRocketRobotOneSided.h"

class RedRocketRobotOneSidedJumping : public RedRocketRobotOneSided
{
	//Chiều dài đoạn mà nó nhảy tới.
	const int jumpLengthForward = 50;

	//Chiều dài đoạn mà nó nhảy lùi.
	const int jumpLengthBackward = 20;

	//Độ cao mà nó nhảy tới.
	const int jumpHeightForward = 100;

	//Độ cao mà nó nhảy lùi.
	const int jumpHeightBackward = 50;
public:
	RedRocketRobotOneSidedJumping(int posX, int posY) : RedRocketRobotOneSided(posX, posY) {};
	~RedRocketRobotOneSidedJumping() {};
	void ChangeState(State newState) override
	{
		currentStateTime = 0;
		switch (newState)
		{
		case State::BEATEN:
			currentBeatenTick = 0;
			flashingTick = 0;
			isBeingBeaten = true;
			this->currentAnimation = shocking;
			--health;
			if (health == 0)
				this->vx = Shield::getInstance()->vx / 10;
			break;
		case State::STANDING:
			this->currentAnimation = standing;
			this->vy = 0;
			break;
		case State::WALKING:
			this->currentAnimation = walking;
			this->vy = 0;
			break;
		case State::DUCKING:
			this->currentAnimation = crouching;
			break;
		case State::DEAD:
			this->currentAnimation = explodeAnim;
			this->vx = Shield::getInstance()->vx / 3;
			break;
		case State::JUMPING:
		{
			this->currentAnimation = crouching;
			this->prevJumpY = pos.y;
			//Lấy jumpHeight dựa trên việc nó đi tới hay đi lùi.
			//Nếu đi tới.
			int jumpHeight = -1;
			int jumpLength = -1;
			if (isMovingLeftToRight && direction == MoveDirection::LeftToRight || !isMovingLeftToRight && direction == MoveDirection::RightToLeft)
			{
				jumpHeight = jumpHeightForward;
				jumpLength = jumpLengthForward;
			}
			else
			{
				jumpHeight = jumpHeightBackward;
				jumpLength = jumpLengthBackward;
			}
				
			//Lấy toạ độ tiếp đất.
			if (isMovingLeftToRight)
				destJumpX = this->pos.x + jumpLength;
			else
				destJumpX = this->pos.x - jumpLength;
			this->vy = (2 * jumpHeight*abs(this->vx)) / jumpLength;
			break;
		}
		case State::FALLING:
			this->currentAnimation = crouching;
			if (this->vy > 0)
				this->vy *= (-1);
			else if (this->vy == 0)
				this->vy = -1;
		}

		previousState = this->robotState;
		this->robotState = newState;
	}
};