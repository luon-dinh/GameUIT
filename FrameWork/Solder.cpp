#include"Solder.h"
#include"Camera.h"
#include "SceneManager.h"

Solder::Solder(RunType runType, float x, float y)
{
	this->tag = Tag::BLUESOLDIER;
	LoadAllAnimation();
	this->vy = 0;
	this->vx = 0;
	this->pos.x = x;
	this->pos.y = y;
	this->runType = runType;
	this->canJump = true;
	this->health = 2;
	this->onAirState = OnAir::None;
	this->delayBeaten = 0;
	this->delayToDead = 0;
	this->currentAnimation = animations[State::STANDING];
	auto player = Player::getInstance();
	float deltax = this->pos.x - player->pos.x;
	if (deltax > 0)
		this->direction = Player::MoveDirection::RightToLeft;
	else
	{
		this->direction = Player::MoveDirection::LeftToRight;
	}
	if (runType == RunType::SPECIAL||runType==RunType::CANRUN)
		//this->stateName = State::RUNNING;
		ChangeState(State::RUNNING);
	else
	{
		ChangeState(State::STANDING);
		//this->stateName = State::STANDING;
	}
	//this->currentAnimation = animations[stateName];
}

float Solder::PosToBottom()
{
	auto sprite = this->currentAnimation->getSprite(this->currentAnimation->curframeindex);
	RECT rect = sprite->getRECT();
	return (rect.top + rect.bottom) / 2 - rect.bottom;
}

Solder::~Solder() {

}

BoundingBox Solder::getBoundingBox()
{
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	auto sprite = this->currentAnimation->getSprite(this->currentAnimation->curframeindex);
	RECT rect = sprite->getRECT();
	height = rect.top - rect.bottom;
	width = rect.right - rect.left;
	box.top = this->pos.y + height / 2;
	box.bottom = this->pos.y - height / 2;
	box.left = this->pos.x - width / 2;
	box.right = this->pos.x + width / 2;
	return box;
}

float Solder::getHeight()
{
	auto sprite = this->currentAnimation->getSprite(this->currentAnimation->curframeindex);
	RECT rect = sprite->getRECT();
	height = rect.top - rect.bottom;
	return height;
}

float Solder::getWidth()
{
	auto sprite = this->currentAnimation->getSprite(this->currentAnimation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	return width;
}

void Solder::OnCollision(Object* object, collisionOut* colOut) {
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
		this->vy = 0;
		this->onAirState = OnAir::None;
		this->pos.y = object->getBoundingBox().top + this->getHeight() / 2;
		break;
	case Type::WATERRL:
		DeactivateObjectInGrid();
		break;
	default:
		break;
	}
	if (object->tag == Tag::SHIELD)
	{
		auto shield = Shield::getInstance();
		if (shield->state == Shield::ShieldState::Attack)
		{
			if (shield->direction == MoveDirection::LeftToRight)
				this->vx = 1;
			else
			{
				this->vx = -1;
			}
			this->health -= 2;
			if (this->health <= 0)
			{
				this->ChangeState(State::DEAD);
			}
			this->isCollidable = false;
			//this->health -= shield->GetCollisionDamage(); chưa có hàm getdamage của shield
		}
	}
	if (object->tag == Tag::PLAYER)
	{
		auto player = Player::getInstance();
		this->health -= player->GetCollisionDamage();
		if (this->health <= 0)
		{
			this->ChangeState(State::DEAD);
		}
		this->isCollidable = false;
	}
}

bool Solder::OnRectCollided(Object* object, CollisionSide side)
{
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
		this->vy = 0;
		break;
	case Type::WATERRL:
		DeactivateObjectInGrid();
	default:
		break;
	}
	if (object->tag == Tag::SHIELD)
	{
		auto shield = Shield::getInstance();
		if (shield->state == Shield::ShieldState::Attack)
		{
			if (shield->direction == MoveDirection::LeftToRight)
				this->vx = 1;
			else
			{
				this->vx = -1;
			}
			this->health -= 2;
			if (this->health <= 0)
			{
				this->ChangeState(State::DEAD);
			}
			this->isCollidable = false;
			//this->health -= shield->GetCollisionDamage(); chưa có hàm getdamage của shield
		}
	}
	if (object->tag == Tag::PLAYER)
	{
		auto player = Player::getInstance();
		this->health -= player->GetCollisionDamage();
		if (this->health <= 0)
		{
			this->ChangeState(State::DEAD);
		}
		this->isCollidable = false;
	}
	return false;
}

void Solder::OnNotCollision(Object* object)
{
	if (object->type == Type::GROUND)
	{
		this->vy -= 0.3;
		if (this->vy > 0)
			this->onAirState == OnAir::Jumping;
		else
		{
			this->onAirState == OnAir::Falling;
		}
	}
}


void Solder::Update(float dt)
{
	if (stateName == State::DEAD)
	{
		if (this->currentAnimation == explodeAnim && this->currentAnimation->curframeindex == this->currentAnimation->toframe - 1)
		{
			DeactivateObjectInGrid();
		}
	}
	if (this->isCollidable == false)
	{
		this->delayBeaten += dt;
	}
	if (this->delayBeaten >= maxDelayBeaten)
	{
		this->delayBeaten = 0;
		this->isCollidable = true;
	}
	if (runType == RunType::NOTRUN||runType==RunType::THREESHOOTER)
	{
		auto player = Player::getInstance();
		float deltax = this->pos.x - player->pos.x;
		if (deltax > 0)
			this->direction = Player::MoveDirection::RightToLeft;
		else
		{
			this->direction = Player::MoveDirection::LeftToRight;
		}
	}
		
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	auto shield = Shield::getInstance();
	this->currentAnimation->Update(dt);
	//tùy theo trạng thái hiện tại mà thay đổi trạng thái
	switch (this->stateName)
	{
	case State::DUCKING:
		if (timeCurrentState >= BLUE_SOLDER_DUCKING_TIME)
		{
			ChangeState(State::STANDING);
		}
		else
		{
			timeCurrentState += dt;
		}

		break;
	case State::STANDING:
		if (timeCurrentState < BLUE_SOLDER_STANDING_TIME)
		{
			if (runType !=RunType::SPECIAL)
			{
				if (timeCurrentState + dt >= BLUE_SOLDER_STANDING_TIME / 2 && timeCurrentState < BLUE_SOLDER_STANDING_TIME / 2)
				{
					auto scene = SceneManager::getInstance();
						
					auto bullet = new BulletSolder(this->direction);
					bullet->existTime = 0;
					bullet->pos.y = this->getBoundingBox().top - 4;
					bullet->pos.x = this->pos.x;
					scene->AddObjectToCurrentScene(bullet);
					if (runType == RunType::THREESHOOTER)
					{
						auto bullet1 = new BulletSolder(this->direction);
						bullet1->vy = -0.5;
						bullet1->existTime = 0;
						bullet1->pos.y = this->getBoundingBox().top - 4;
						bullet1->pos.x = this->pos.x;
						scene->AddObjectToCurrentScene(bullet1);
						auto bullet2 = new BulletSolder(this->direction);
						bullet2->vy = 0.5;
						bullet2->existTime = 0;
						bullet2->pos.y = this->getBoundingBox().top - 4;
						bullet2->pos.x = this->pos.x;
						scene->AddObjectToCurrentScene(bullet2);
					}
				}
			}
			timeCurrentState += dt;
		}
		else
		{
			if (runType == RunType::NOTRUN || runType == RunType::THREESHOOTER)
			{
				ChangeState(State::DUCKING);
			}
			else
			{
				ChangeState(State::RUNNING);
			}
		}
		break;
	case State::RUNNING:
		if (runType==RunType::SPECIAL)
		{
			if (shield->state == Shield::ShieldState::Attack&&shield->GetMoveDirection() != this->direction)
			{
				if (canJump)
				{
					ChangeState(State::JUMPING);
					canJump = false;
				}
			}
		}
		if (timeCurrentState > BLUE_SOLDER_RUNNING_TIME)
		{
			if (runType == RunType::CANRUN)
				ChangeState(State::STANDING);
		}
		else
		{
			timeCurrentState += dt;
		}	
		break;
	case State::DEAD:
		if (delayToDead>=currentAnimation->tiperframe)
		{
			if(this->currentAnimation != this->explodeAnim)
			{
				this->currentAnimation = this->explodeAnim;
			}
		}
		else
		{
			delayToDead += dt;
		}
		break;
	case State::JUMPING:
		this->vy -= GROUND_GRAVITY;
		deltaY += this->vy;
		if (deltaY >= 60 && onAirState == OnAir::Jumping)
			onAirState == OnAir::Falling;
	default:
		break;
	}
}

void Solder::Render()
{
	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	if (!this->isCollidable)
	{
		if ((int)this->timeCurrentState % 2 == 0)
		{
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
	}
	else
	{
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
}


void Solder::LoadAllAnimation()
{
	animations[State::RUNNING] = new Animation(Tag::BLUESOLDIER, 0, 3);// run
	animations[State::STANDING] = new Animation(Tag::BLUESOLDIER, 3, 4);//stand
	animations[State::DUCKING] = new Animation(Tag::BLUESOLDIER, 4, 5);//duck
	animations[State::DEAD] = new Animation(Tag::BLUESOLDIER, 5, 6);//dead
}

void Solder::ChangeState(State stateName)
{
	/*if (stateName == this->stateName)
		return;*/
	this->timeCurrentState = 0;
	float pos1 = this->PosToBottom();
	this->stateName = stateName;
	switch (stateName)
	{
	case State::STANDING:
		this->currentAnimation = animations[State::STANDING];
		this->vx = 0;
		this->vy = 0;
		isDead = false;
		this->onAirState == OnAir::None;
		break;
	case State::RUNNING:
		this->vy = 0;
		this->currentAnimation = animations[State::RUNNING];
		if (this->direction == Player::MoveDirection::LeftToRight)
			this->vx = ENEMY_SPEED* PLAYER_NORMAL_SPEED;
		else
			this->vx = -ENEMY_SPEED*PLAYER_NORMAL_SPEED;
		isDead = false;
		if (runType == RunType::SPECIAL)
			this->vx *= 1.5;
		this->onAirState == OnAir::None;
		break;
	case State::DUCKING:
		this->currentAnimation = animations[State::DUCKING];
		this->vx = 0;
		this->vy = 0;
		isDead = false;
		this->onAirState == OnAir::None;
		break;
	case State::DEAD:
		this->currentAnimation = animations[State::DEAD];
		break;
	case State::JUMPING:
		this->vy = 10;
		this->onAirState == OnAir::Jumping;
		break;
	default:
		break;
	}
	float pos2 = this->PosToBottom();
	this->pos.y = this->pos.y + (pos2 - pos1);
}
