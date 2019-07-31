#include"Solder.h"
#include"Camera.h"
#include "SceneManager.h"

Solder::Solder(RunType runType)
{
	this->tag = Tag::BLUESOLDIER;
	LoadAllAnimation();
	timeCurrentState = 0;
	this->vy = 0;
	this->runType = runType;
	this->canJump = true;
	this->direction = Player::MoveDirection::RightToLeft;
	if (runType == RunType::SPECIAL)
		ChangeState(State::RUNNING);
	else
	{
		ChangeState(State::STANDING);
	}
}

Solder::~Solder() {

}

BoundingBox Solder::getBoundingBox()
{
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	box.left = this->pos.x - 12;
	box.right = this->pos.x + 12;
	switch (this->stateName)
	{
	case State::RUNNING:
	case State::STANDING:
		box.top = this->pos.y + 22;
		box.bottom = this->pos.y - 21;
		return box;
	case State::DUCKING:
		box.top = this->pos.y + 6;
		box.bottom = this->pos.y - 21;
		return box;
	default:
		box.top = this->pos.y + 11;
		box.bottom = this->pos.y - 21;
		return box;
	}
}


void Solder::OnCollision(Object* object, collisionOut* colOut) {
	this->onAirState == OnAir::None;
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
		this->vy = 0;
		this->pos.y = object->getStaticObjectBoundingBox().top + this->getHeight() / 2;
		ChangeState(State::RUNNING);
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
			ChangeState(State::BEATEN);
		}
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
			ChangeState(State::BEATEN);
		}
	}
	return true;
}

void Solder::OnNotCollision(Object* object)
{
	this->vy -= GROUND_GRAVITY;
	if(this->vy>0)
		this->onAirState == OnAir::Jumping;
	else
	{
		this->onAirState == OnAir::Falling;
	}
}


void Solder::Update(float dt)
{
	if (!isDead)
	{
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
				if (runType == RunType::NOTRUN|| runType == RunType::CANRUN)
				{
					if (timeCurrentState + dt >= BLUE_SOLDER_STANDING_TIME / 2 && timeCurrentState < BLUE_SOLDER_STANDING_TIME / 2)
					{
						auto scene = SceneManager::getInstance();
						auto bullet = new BulletSolder();
						bullet->existTime = 0;
						bullet->direction = this->direction;
						bullet->pos.y = this->getBoundingBox().top - 4;
						bullet->pos.x = this->pos.x;
  						scene->AddObjectToCurrentScene(bullet);
						if (runType == RunType::THREESHOOTER)
						{
							auto bullet1 = new BulletSolder();
							bullet1->vy = -0.5;
							bullet1->existTime = 0;
							bullet1->direction = this->direction;
							bullet1->pos.y = this->getBoundingBox().top - 4;
							bullet1->pos.x = this->pos.x;
							scene->AddObjectToCurrentScene(bullet1);
							auto bullet2 = new BulletSolder();
							bullet2->vy = 0.5;
							bullet2->existTime = 0;
							bullet2->direction = this->direction;
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
				if(runType==RunType::NOTRUN||runType==RunType::THREESHOOTER)
					ChangeState(State::DUCKING);
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
		case State::BEATEN:
			if (timeCurrentState > ENEMY_BEATEN_TIME)
				ChangeState(State::DEAD);
			else
			{
				timeCurrentState += dt;
			}
			break;
		case State::DEAD:
			if (currentAnimation->curframeindex == currentAnimation->toframe - 1)
			{
				DeactivateObjectInGrid();
			}
			break;
		case State::JUMPING:
			this->vy -= GROUND_GRAVITY;
			deltaY += this->vy;
			if (deltaY >= 60&&onAirState==OnAir::Jumping)
				onAirState == OnAir::Falling;
		default:
			break;
		}
	}
}

void Solder::Render()
{
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


void Solder::LoadAllAnimation()
{
	animations[State::RUNNING] = new Animation(Tag::BLUESOLDIER, 0, 3);// run
	animations[State::STANDING] = new Animation(Tag::BLUESOLDIER, 3);//stand
	animations[State::DUCKING] = new Animation(Tag::BLUESOLDIER, 4);//duck
	animations[State::BEATEN] = new Animation(Tag::BLUESOLDIER, 5);//beaten
}

void Solder::ChangeState(State stateName)
{
	
	switch (stateName)
	{
	case State::STANDING:
		this->currentAnimation = animations[State::STANDING];
		this->vx = 0;
		isDead = false;
		this->onAirState == OnAir::None;
		break;
	case State::RUNNING:
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
		isDead = false;
		this->onAirState == OnAir::None;
		break;
	case State::BEATEN:
		this->currentAnimation = animations[State::BEATEN];
		this->vx = this->vy = 0;
		if (this->direction == Player::MoveDirection::LeftToRight)
			this->pos.x -= 3;
		else
		{
			this->pos.x += 3;
		}
		break;
	case State::DEAD:
		this->currentAnimation = explodeAnim;
		break;
	case State::JUMPING:
		this->vy = 10;
		this->onAirState == OnAir::Jumping;
		break;
	default:
		break;
	}
	this->stateName = stateName;
	timeCurrentState = 0;
}
