#include "RedRocketRobotTwoSided.h"
#include "BulletRedRocketLinear.h"
#include "SceneManager.h"

RedRocketRobotTwoSided::RedRocketRobotTwoSided(int posX, int posY) : RedRocketRobot(posX, posY)
{
	//Cập nhật lại vận tốc đi theo hướng của robot.
	if (direction == MoveDirection::LeftToRight)
		this->vx = walkingSpeed;
	else
		this->vx = -walkingSpeed;
	this->currentAnimation = walking;
	//Con này bắn đạn chậm hơn.
	this->rocketSpeed = 3;
	ChangeState(State::FALLING);
}

RedRocketRobotTwoSided::~RedRocketRobotTwoSided()
{

}

void RedRocketRobotTwoSided::Update(float dt)
{
	currentStateTime += dt;
	//Cập nhật thời gian cho trạng thái beaten (chớp chớp).
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
	//Trạng thái đi.
	if (robotState == State::WALKING)
		EnemyWalkingUpdate(dt);
	else if (robotState == State::JUMPING || robotState == State::FALLING)
		EnemyJumpingUpdate(dt);
	else if (robotState == State::STANDING || robotState == State::DUCKING)
		EnemyAttackingUpdate(dt);
	else if (robotState == State::BEATEN)
		EnemyBeatenUpdate(dt);
	else if (robotState == State::DEAD)
		EnemyDeadUpdate(dt);
	this->currentAnimation->Update(dt);
}

void RedRocketRobotTwoSided::EnemyWalkingUpdate(double dt)
{
	if (gone < walkingDistant)
	{
		if (Shield::getInstance()->state == Shield::ShieldState::Attack && Shield::getInstance()->GetMoveDirection() != this->direction)
		{
			//Chỉ nhảy khi thấy player ném khiên.
			//Nếu player đang đứng bên trái của robot.
			if (player->pos.x > this->pos.x && this->direction == MoveDirection::LeftToRight)
			{
				//Nếu ném khiên.
				ChangeState(State::JUMPING);
			}
			else if (player->pos.x < this->pos.x && this->direction == MoveDirection::RightToLeft)
			{
				ChangeState(State::JUMPING);
			}
		}
		else
		{
			this->pos.x += this->vx;
			gone += abs(this->vx);
		}
	}
	else //Nếu đã đi đủ rồi thì chuyển qua trạng thái khác.
	{
		ChangeState(State::STANDING);
	}
}

void RedRocketRobotTwoSided::EnemyAttackingUpdate(double dt)
{
	currentFiringTick += dt;

	//Hướng mặt về phía player.
	if (this->pos.x < player->pos.x)
		direction = MoveDirection::LeftToRight;
	else
		direction = MoveDirection::RightToLeft;

	//Nếu thời gian chờ đã đủ lâu thì ta đổi trạng thái.
	if (currentStateTime > attackingStateTime)
	{
		if (robotState == State::STANDING)
			ChangeState(State::DUCKING);
		else if (robotState == State::DUCKING)
			ChangeState(State::STANDING);
		return;
	}

	//Đủ thời gian chờ thì ta bắn luôn.
	if (!isAttacked && currentStateTime > attackingDelay)
	{
		if (robotState == State::STANDING)
			currentAnimation = standShooting;
		else
			currentAnimation = crouchShooting;
		if (currentAnimation->curframeindex == currentAnimation->toframe - 1)
		{
			currentFiringTick = 0;
			isAttacked = true;
			Fire();
		}
	}
	else
	{
		currentAnimation->curframeindex = 0;
		if (robotState == State::STANDING)
			currentAnimation = standing;
		else
			currentAnimation = crouching;
	}
}

void RedRocketRobotTwoSided::EnemyBeatenUpdate(double dt)
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

void RedRocketRobotTwoSided::EnemyDeadUpdate(double dt)
{
	if (robotState == State::DEAD) //Nổ tung và deactivate nó.
	{
		if (currentStateTime > explodeTime)
		{
			SoundManager::getinstance()->play(SoundManager::SoundName::object_explode);
			DeactivateObjectInGrid();
			return;
		}
	}
}

void RedRocketRobotTwoSided::Render()
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

void RedRocketRobotTwoSided::EnemyJumpingUpdate(double dt)
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

void RedRocketRobotTwoSided::ChangeState(State newState)
{
	float previousYToBottom = PosToBottom();
	currentStateTime = 0;
	switch (newState)
	{
	case State::BEATEN:
		currentBeatenTick = 0;
		flashingTick = 0;
		isBeingBeaten = true;
		this->currentAnimation = shocking;
		if (health <= 0)
			this->vx = Shield::getInstance()->vx / 10;
		break;
	case State::STANDING:
		this->currentAnimation = standing;
		isAttacked = false;
		break;
	case State::WALKING:
		this->currentAnimation = walking;
		this->vy = 0;
		break;
	case State::DUCKING:
	{
		this->currentAnimation = crouching;
		isAttacked = false;
		float thisYToBottom = PosToBottom();
		this->pos.y -= previousYToBottom - thisYToBottom;
		break;
	}
	case State::DEAD:
		this->currentAnimation = explodeAnim;
		break;
	case State::JUMPING:
		this->currentAnimation = crouching;
		if (direction == MoveDirection::LeftToRight)
			destJumpX = this->pos.x + jumpLength;
		else
			destJumpX = this->pos.x - jumpLength;
		this->vy = (2 * jumpHeight*abs(this->vx)) / jumpLength;
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

	
}

void RedRocketRobotTwoSided::OnCollision(Object* object, collisionOut * colOut)
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
				//Nếu đi chưa hết đoạn đường thì chuyển sang state walking.
				if (isFirstTimeFalling)
				{
					isFirstTimeFalling = false;
					ChangeState(State::WALKING);
				}
				else
					ChangeState(State::STANDING);
					
				this->pos.y -= colOut->collisionTime * vy;
			}
			this->SetStandingGround(object);
		}
	}
}

void RedRocketRobotTwoSided::Fire()
{
	if (robotState == State::DUCKING)
		SceneManager::getInstance()->AddObjectToCurrentScene(new BulletRedRocketLinear(direction, this->pos.x, this->pos.y, rocketSpeed));
	else
		SceneManager::getInstance()->AddObjectToCurrentScene(new BulletRedRocketLinear(direction, this->pos.x, this->pos.y + 15, rocketSpeed));
}

bool RedRocketRobotTwoSided::OnRectCollided(Object* object, CollisionSide colOut)
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

void RedRocketRobotTwoSided::OnNotCollision(Object * object)
{
	if (object->type == Type::GROUND && !this->StandOnCurrentGround() && this->robotState == State::WALKING)
	{
		ChangeState(State::JUMPING);
	}
}