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
	ChangeState(State::FALLING);
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
	//Kiểm tra có đang bị beaten hay không để phục vụ xét va chạm.
	if (isBeingBeaten)
	{
		currentBeatenTick += dt;
		flashingTick += dt;
		isCollidable = false;
		if (currentBeatenTick > beatenTime)
		{
			isBeingBeaten = false;
			isCollidable = true;
		}
			
	}
	
	currentStateTime += dt;

	if (robotState == State::WALKING)
		EnemyAliveUpdate(dt);
	else if (robotState == State::STANDING || robotState == State::DUCKING)
		EnemyAttackingUpdate(dt);
	else if (robotState == State::JUMPING || robotState == State::FALLING)
		EnemyJumpingUpdate(dt);
	else if (robotState == State::BEATEN)
		EnemyBeatenUpdate(dt);
	else if (robotState == State::DEAD)
		EnemyDeadUpdate(dt);

	this->currentAnimation->Update(dt);
}

void RedRocketRobotOneSided::EnemyJumpingUpdate(double dt)
{
	//Khi vẫn còn trong trạng thái nhảy lên thì nhảy lên.
	if (robotState == State::JUMPING)
	{
		if (abs(this->pos.x - destJumpX) > jumpLength / 2)
		{
			this->pos.y += this->vy;
			this->pos.x += this->vx;
		}
		else
		{
			ChangeState(State::FALLING);
		}
	}

	else if (robotState == State::FALLING)
	{
		this->pos.y += this->vy;
		this->pos.x += this->vx;
	}
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
		//Nếu mặt đang hướng theo hướng player, đi đến player và player chọi khiên thì nhảy.
		if (Shield::getInstance()->state == Shield::ShieldState::Attack && Shield::getInstance()->GetMoveDirection() != this->direction)
		{
			//Chỉ nhảy khi thấy player ném khiên.
			//Nếu player đang đứng bên trái của robot.
			if (player->pos.x > this->pos.x && isMovingLeftToRight && this->direction == MoveDirection::LeftToRight)
			{
				//Nếu ném khiên.
				ChangeState(State::JUMPING);
			}
			else if (player->pos.x < this->pos.x && !isMovingLeftToRight && this->direction == MoveDirection::RightToLeft)
			{
				ChangeState(State::JUMPING);
			}
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
	if (isAttacked)	{
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
		{
			return;
		}	
		else if (!isAttacked)
		{
			currentAnimation = crouchShooting;
			if (currentAnimation->curframeindex == currentAnimation->toframe - 1)
			{
				SceneManager::getInstance()->AddObjectToCurrentScene(new BulletRedRocketLinear(this->direction, this->pos.x, this->pos.y + 15, rocketSpeed));
				isAttacked = true;
			}
		}
	}
}

void RedRocketRobotOneSided::EnemyBeatenUpdate(double dt)
{
	//Xét xem, nếu hết máu thì xử lý theo cách khác.
	if (health <= 0)
	{
		isBeingBeaten = false;
		this->pos.x += this->vx;
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
			Player::getInstance()->ScoreUp(this->score);
			SoundManager::getinstance()->play(SoundManager::SoundName::object_explode);
			DeactivateObjectInGrid();
			return;
		}
	}
}

void RedRocketRobotOneSided::ChangeState(State newState)
{
	float previousYToBottom = PosToBottom();
	currentStateTime = 0;
	switch (newState)
	{
	case State::BEATEN:
	{
		currentBeatenTick = 0;
		flashingTick = 0;
		isBeingBeaten = true;
		this->currentAnimation = shocking;
		if (health <= 0)
			this->vx = Shield::getInstance()->vx / 10;
		float thisYToBottom = PosToBottom();
		this->pos.y -= previousYToBottom - thisYToBottom;
		break;
	}
	case State::STANDING:
	{
		this->currentAnimation = standing;
		this->vy = 0;
		float thisYToBottom = PosToBottom();
		this->pos.y -= previousYToBottom - thisYToBottom;
		break;
	}
		
	case State::WALKING:
		this->currentAnimation = walking;
		this->vy = 0;
		break;
	case State::DUCKING:
	{
		this->currentAnimation = crouching;
		float thisYToBottom = PosToBottom();
		this->pos.y -= previousYToBottom - thisYToBottom;
		break;
	}
	case State::DEAD:
		this->currentAnimation = explodeAnim;
		this->vx = Shield::getInstance()->vx / 3;
		break;
	case State::JUMPING:
		this->currentAnimation = crouching;
		this->prevJumpY = pos.y;
		if (isMovingLeftToRight)
			destJumpX = this->pos.x + jumpLength;
		else
			destJumpX = this->pos.x - jumpLength;
		this->vy = (2*jumpHeight*abs(this->vx))/jumpLength;
		break;
	case State::FALLING:
		this->currentAnimation = crouching;
		if (this->vy > 0)
			this->vy *= (-1);
		else if (this->vy == 0)
			this->vy = -1;
	}
	previousState = this->robotState;
	this->robotState = newState;

	float thisYToBottom = PosToBottom();
	//this->pos.y -= previousYToBottom - thisYToBottom;
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
			{
				health -= object->GetCollisionDamage();
				ChangeState(State::BEATEN);
			}
		} 
	}
	else if (object->tag == Tag::STATICOBJECT)
	{
		//Chỉ chuyển sang trạng thái standing khi đang rơi.
		if ( (object->type == Type::GROUND || object->type == Type::SOLIDBOX)  && colOut->side == CollisionSide::bottom)
		{
			if (robotState == State::FALLING)
			{
				if (isFirstTimeFalling)
				{
					isFirstTimeFalling = false;
					this->pos.y += (2 * object->height / 3);
					ChangeState(State::WALKING);
				}
				else
					ChangeState(State::STANDING);
				this->pos.y -= colOut->collisionTime * vy + (2 * object->height / 3);
			}
			this->SetStandingGround(object);
		}
	}
}

bool RedRocketRobotOneSided::OnRectCollided(Object* object, CollisionSide colOut)
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
	else if (object->tag == Tag::PLAYER || object->tag == Tag::PLAYER_PART)
	{
		if (!isBeingBeaten)
		{
			health -= object->GetCollisionDamage();
			ChangeState(State::BEATEN);
		}
	}
	else if (object->tag == Tag::STATICOBJECT)
	{
		return false;
	}
	return true;
}

void RedRocketRobotOneSided::OnNotCollision(Object * object)
{
	if (object->type == Type::GROUND && !this->StandOnCurrentGround() && this->robotState == State::WALKING)
	{
		ChangeState(State::JUMPING);
	}
}