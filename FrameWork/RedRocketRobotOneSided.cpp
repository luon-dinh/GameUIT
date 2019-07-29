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

	//Cập nhật thời gian cho trạng thái beaten (chớp chớp).
	if (isBeingBeaten)
	{
		currentBeatenTick += dt;
		flashingTick += dt;
		if (currentBeatenTick > beatenTime)
			isBeingBeaten = false;
	}
	
	currentStateTime += dt;

	if (robotState == State::WALKING)
		EnemyAliveUpdate(dt);
	else if (robotState == State::STANDING || robotState == State::DUCKING)
		EnemyAttackingUpdate(dt);

	else if (robotState == State::BEATEN)
		EnemyBeatenUpdate(dt);

	else if (robotState == State::DEAD)
		EnemyDeadUpdate(dt);

	this->currentAnimation->Update(dt);
}

void RedRocketRobotOneSided::Render()
{
	//Nếu đang ở trạng thái beaten mà thời gian chưa đủ để render tiếp thì không render.
	if (isBeingBeaten && flashingTick < delayBeatenSprite / 2)
	{
		return;
	}
	flashingTick = 0;
	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	switch (this->direction)
	{
	case Player::MoveDirection::LeftToRight:
		this->currentAnimation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
		break;
	case Player::MoveDirection::RightToLeft:
		this->currentAnimation->Render(pos);
		break;
	default:
		break;
	}
}

void RedRocketRobotOneSided::EnemyAliveUpdate(double dt)
{
	currentWalkingTick += dt;
	if (isMovingLeftToRight && this->pos.x <= maxX || !isMovingLeftToRight && this->pos.x >= minX)
	{
		//Chỉ khi đạt đủ delay thì mới cho phép đi.
		if (currentWalkingTick >= walkingDelay)
		{
			this->pos.x += this->vx;
			currentWalkingTick = 0;
		}
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
			SceneManager::getInstance()->AddObjectToCurrentScene(new BulletRedRocketLinear(this->direction, this->pos.x, this->pos.y, rocketSpeed));
			isAttacked = true;
		}
	}
}

void RedRocketRobotOneSided::EnemyBeatenUpdate(double dt)
{
	//Xét xem, nếu hết máu thì xử lý theo cách khác.
	if (health <= 0)
	{
		isBeingBeaten = false;
		if (currentStateTime > deadShockingTime)
			ChangeState(State::DEAD);
		return;
	}
	//Nếu đủ thời gian shocking thì chuyển lại qua trạng thái trước đó.
	if (currentStateTime > shockingTime)
	{
		ChangeState(previousState);
		return;
	}
}

void RedRocketRobotOneSided::EnemyDeadUpdate(double dt)
{
	if (robotState == State::DEAD) //Nổ tung và deactivate nó.
	{
		if (currentStateTime > explodeTime)
		{
			DeactivateObjectInGrid();
			return;
		}
	}
}

void RedRocketRobotOneSided::ChangeState(State newState)
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
	case State::DEAD:
		this->currentAnimation = explodeAnim;
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

void RedRocketRobotOneSided::OnCollision(Object* object, collisionOut* colOut)
{
	if (object->tag == Tag::SHIELD)
	{
		Shield *shield = Shield::getInstance();
		if (shield->state == Shield::ShieldState::Attack)
		{
			//Nếu đang không bị beaten thì mới chuyển trạng thái.
			if (!isBeingBeaten)
				ChangeState(State::BEATEN);
		}
	}
}