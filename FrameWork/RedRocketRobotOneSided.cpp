#include "RedRocketRobotOneSided.h"
#include "SceneManager.h"

RedRocketRobotOneSided::RedRocketRobotOneSided(int posX, int posY) : RedRocketRobot(posX, posY)
{
	//Tính khoảng cách tối đa robot đi được.
	minX = posX - walkRange / 2;
	maxX = posX + walkRange / 2;
	
	if (direction == MoveDirection::LeftToRight)
		isMovingLeftToRight = true;
	else
		isMovingLeftToRight = false;
}

RedRocketRobotOneSided::~RedRocketRobotOneSided()
{

}

void RedRocketRobotOneSided::Update(float dt)
{
	if (isMovingLeftToRight)
		this->vx = walkingSpeed;
	else
		this->vx = -walkingSpeed;

	if (robotState == State::WALKING)
	{
		EnemyAliveUpdate(dt);
	}
	else if (robotState == State::STANDING || robotState == State::DUCKING)
		EnemyAttackingUpdate(dt);
	else if (robotState == State::BEATEN)
		EnemyBeatenUpdate(dt);
	else if (robotState == State::DEAD)
		EnemyDeadUpdate(dt);

	this->currentAnimation->Update(dt);
}

void RedRocketRobotOneSided::EnemyAliveUpdate(double dt)
{
	if (isMovingLeftToRight && this->pos.x <= maxX || !isMovingLeftToRight && this->pos.x >= minX)
	{
		this->pos.x += this->vx;
	}
	else //Dừng lại và bắn.
	{
		ChangeState(State::STANDING);
	}
}

void RedRocketRobotOneSided::EnemyAttackingUpdate(double dt)
{
	//Xét nếu đã tấn công rồi thì ta xử lý riêng.
	if (isAttacked)
	{
		if (robotState == State::DUCKING)
		{
			if (currentStateTime > crouchingState)
				ChangeState(State::STANDING);
		}

		if (robotState == State::STANDING)
		{
			if (currentStateTime > standingToWalkingDelay)
			{
				ChangeState(State::WALKING);
				ChangeMoveDirection();
				isAttacked = false;
			}
		}
		return;
	}
	
	//Trường hợp chưa tấn công.
	if (robotState == State::STANDING)
	{
		//Nếu chưa đủ thời gian đứng lại thì vẫn cho đứng tiếp.
		if (currentStateTime < standingDelay)
			return;
		else //Nếu đã đủ thời gian đứng thì chuyển sang trạng thái ngồi (trong TH chưa bắn).
			ChangeState(State::DUCKING);
	}
	
	if (robotState == State::DUCKING)
	{
		if (currentStateTime < attackingDelay)
			return;
		else if (!isAttacked)
		{
			SceneManager::getInstance()->AddObjectToCurrentScene(new BulletRedRocket(this->direction, this->pos.x, this->pos.y, rocketSpeed));
			isAttacked = true;
		}
	}
}

void RedRocketRobotOneSided::EnemyBeatenUpdate(double dt)
{
	//Trạng thái khi nhân vật "ăn đòn" của player.

}

void RedRocketRobotOneSided::ChangeState(State newState)
{
	currentStateTime = 0;
	switch (newState)
	{
	case State::BEATEN:
		break;
	case State::STANDING:
		this->currentAnimation = standing;
		break;
	case State::WALKING:
		this->currentAnimation = walking;
		break;
	case State::DUCKING:
		this->currentAnimation = crouching;
		break;
	}

	previousState = this->robotState;
	this->robotState = newState;
}

void RedRocketRobotOneSided::ChangeMoveDirection()
{
	isMovingLeftToRight = !isMovingLeftToRight;
	this->vx *= (-1);
}