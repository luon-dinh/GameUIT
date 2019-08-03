#include"BossMini.h"
#include"BulletMiniNormal.h"
#include"BulletMiniSpecial.h"
#include"SceneManager.h"

BossMini* BossMini::instance = NULL;

BossMini::BossMini()
{
	LoadAllAnimations();
	auto player = Player::getInstance();
	this->tag = Tag::BOSSMINI;
	this->state = State::FALLING;
	this->currentAnimation = animations[State::STANDING];
	this->timeNotRender = 0;
	this->countTimeBeaten = 0;
	this->vx = 0;
	this->vy = -1.5;
	this->pos.x = 200;
	this->pos.y = 120;
	this->health = maxHelth;
	this->timeCurrentState = 0;
	this->onAirState = OnAir::Falling;
	this->deltaX = 0;
	this->canNewBullet = true;
	this->hasBullet = false;
	float deltaX = this->pos.x - player->pos.x;
	if (deltaX > 0)
		this->direction = MoveDirection::RightToLeft;
	else
	{
		this->direction = MoveDirection::LeftToRight;
	}
}


BossMini* BossMini::getInStance()
{
	if (!instance)
		instance = new BossMini();
	return instance;
}

BossMini::~BossMini()
{

}

void BossMini::LoadAllAnimations()
{
	animations[State::FALLING] = new Animation(Tag::BOSSMINI, 0, 1);
	animations[State::STANDING] = new Animation(Tag::BOSSMINI, 1, 2);
	animations[State::ATTACKING_FLY] = new Animation(Tag::BOSSMINI, 2, 4, maxTimeStateDelay/2);
	animations[State::ATTACK] = new Animation(Tag::BOSSMINI, 4, 5, maxTimeStateDelay);
	animations[State::RUNNING] = new Animation(Tag::BOSSMINI, 5, 8);
	animations[State::BEATEN] = new Animation(Tag::BOSSMINI, 8, 10, maxTimeStateDelay/2);
	animations[State::DEAD] = new Animation(Tag::BOSSMINI, 10, 11);
	animations[State::DASHING] = new Animation(Tag::BOSSMINI, 11, 13);
}

BoundingBox BossMini::getBoundingBox()
{
	auto sprite = currentAnimation->getSprite(currentAnimation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	height = rect.top - rect.bottom;
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	box.top = this->pos.y + height / 2;
	box.bottom = this->pos.y - height / 2;
	box.left = this->pos.x - width / 2;
	box.right = this->pos.x + width / 2;
	return box;

}

float BossMini::getHeight()
{
	auto sprite = currentAnimation->getSprite(currentAnimation->curframeindex);
	RECT rect = sprite->getRECT();
	height = rect.top - rect.bottom;
	return height;
}

float BossMini::getWidth()
{
	auto sprite = currentAnimation->getSprite(currentAnimation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	return width;
}

void BossMini::Update(float dt)
{
	/*if (countBullet >= 3)
		ChangeState(State::RUNNING);*/
	auto player = Player::getInstance();
	switch (this->state)
	{
	case State::STANDING:
		this->vx = this->vy = 0;
		if (timeCurrentState < maxTimeStateDelay)//nếu hết thời gian stand chuyển sang attack
			timeCurrentState +=defaultDT;
		else
		{
			if (countBullet == 0)
			{
				ChangeState(State::ATTACKING_FLY);
			}
			else
			{
				ChangeState(State::ATTACK);
			}
		}
		break;
	case State::RUNNING:// hết khoảng cách run chuyển sang stand
		if (deltaX > maxDelatXRun)
		{
			this->vx = this->vy = 0;
			ChangeState(State::STANDING);
			deltaX = 0;
		}
		else
		{
			deltaX += abs(this->vx);
		}
		if (this->pos.x < minMap&&this->direction==MoveDirection::RightToLeft) // đầu map thì chuyển direction
		{ 
			this->direction = MoveDirection::LeftToRight; 
		}
		if (this->pos.x > maxMap&&this->direction==MoveDirection::LeftToRight)// cuối map thì chuyển direction
		{
			this->direction = MoveDirection::RightToLeft;
		}
		// cập nhật vận tốc theo direction
		if (this->direction == MoveDirection::LeftToRight)
			this->vx = speed;
		else
		{
			this->vx = -speed;
		}
		break;
	case State::FALLING:// rớt thì không làm gì cả
		break;
	case State::ATTACK: // bắn đạn
		if (timeCurrentState < maxTimeStateDelay)// nếu chưa hết thời gian cảu state
		{
			if (timeCurrentState<maxTimeStateDelay / 2 && timeCurrentState + defaultDT>=maxTimeStateDelay/2) //nếu đang ở giữa thời gian của state thì bắn đạn
			{
				auto bullet = new BulletMiniNormal();
				bullet->direction = this->direction;
				bullet->vy = 0;
				bullet->pos.y = this->pos.y + 10;
				if (this->direction == MoveDirection::LeftToRight)
				{
					bullet->vx = bulletSpeed;
					bullet->pos.x = this->pos.x + this->getWidth() / 2;
				}
				else
				{
					bullet->vx = -bulletSpeed;
					bullet->pos.x = this->pos.x - this->getWidth() / 2;
				}
				
				SceneManager::getInstance()->AddObjectToCurrentScene(bullet);
				countBullet++;
			}
			timeCurrentState +=defaultDT;
		}
		else
		{
			if (countBullet < maxBullet)//nếu chưa bắn đủ 2 viên thường thì bắn tiếp
			{
				ChangeState(State::STANDING);
			}
			else// bắn đủ 2 viên thường thì bném thùng
			{
				countBullet = 0;
				ChangeState(State::RUNNING);
			}
		}
		break;
	case State::ATTACKING_FLY://ném thùng
		D3DXVECTOR2 pos1 = D3DXVECTOR2(this->pos.x, this->pos.y+this->getHeight()/2);
		D3DXVECTOR2 pos2;
		pos2.y = this->pos.y + this->getHeight() / 2 + 30;
		float delta = this->pos.x - player->pos.x;
		if (abs(delta) < deltaToThrow)
		{
			pos2.x = (player->pos.x+this->pos.x)/2;
			pos2.y = this->pos.y + this->getHeight() / 2 + 10;
		}
		else
		{
			if (this->direction == MoveDirection::RightToLeft)
			{
				pos2.x = this->pos.x - deltaToThrow;
			}
			else
			{
				pos2.x = this->pos.x + deltaToThrow;
			}
		}
		
		//nếu đến thời điểm ném
		if (timeCurrentState < maxTimeStateDelay)
		{
			if (!hasBullet&&canNewBullet)
			{
				this->defaultBullet = new BulletMiniSpecial(pos1, pos2);
				this->defaultBullet->vy = 0;
				this->defaultBullet->pos.x = this->pos.x;
				this->defaultBullet->pos.y = this->pos.y + this->getHeight() / 2;
				this->defaultBullet->vx = 0;
				SceneManager::getInstance()->AddObjectToCurrentScene(this->defaultBullet);
				hasBullet = true;
				canNewBullet = false;
				countBullet++;
			}

			if (timeCurrentState < maxTimeStateDelay / 2 && timeCurrentState + defaultDT >= maxTimeStateDelay / 2)
			{
				if (this->direction == MoveDirection::RightToLeft)
				{
					this->defaultBullet->vx = -bulletSpeed;
					this->defaultBullet->direction = MoveDirection::RightToLeft;
				}
				else
				{
					this->defaultBullet->direction = MoveDirection::LeftToRight;
					this->defaultBullet->vx = bulletSpeed;
				}
				hasBullet = false;
			}
			timeCurrentState += defaultDT;
		}
		else
		{
			this->canNewBullet = true;
			ChangeState(State::ATTACK);
		}
		break;
	//case State::DEAD:
	//	break;
	//case State::BEATEN:
	//	break;
	//case State::DASHING:// state điên
	//	break;
	/*default:
		break;*/
	}
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	currentAnimation->Update(dt);
}

void BossMini::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, pos.y, 0));

	if (this->direction == Player::MoveDirection::LeftToRight) {
		// move from left to right
		currentAnimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal);
	}
	else {
		currentAnimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
	}
}

void BossMini::ChangeState(State stateName)
{
	auto player = Player::getInstance();
	float delta = this->pos.x - player->pos.x;
	if (delta > 0)
	{
		this->direction = MoveDirection::RightToLeft;
	}
	else
	{
		this->direction = MoveDirection::LeftToRight;
	}
	this->timeCurrentState = 0;
	this->state = stateName;
	this->currentAnimation = animations[stateName];
	switch (stateName)
	{
	case State::STANDING:
	case State::ATTACK:
		this->vx = this->vy = 0;
		break;
	case State::ATTACKING_FLY:
		this->vx = this->vy = 0;
		break;
	}
}

void BossMini::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
		if (colOut->side == CollisionSide::bottom)
		{
			this->vy = 0;
			this->pos.y = object->getBoundingBox().top + this->getHeight() / 2;
			this->onAirState = OnAir::None;
			ChangeState(State::STANDING);
		}
		break;
	default:
		break;
	}
	if(object->tag == Tag::SHIELD)
	{
		auto shield = Shield::getInstance();
		if (shield->state == Shield::ShieldState::Attack)
		{
			//render khong render
			//this->currentanimation = animations[State::DEAD];
			this->health -= shield->GetCollisionDamage();
			if (this->health <= 0)
			{
				//isDead = true;
				ChangeState(State::DEAD);
			}
			//this->isCollide = true;
			return;
		}
	}
	if (object->tag == Tag::PLAYER)
	{
		this->health -= Player::getInstance()->GetDamage();
		this->isCollidable = false;
		return;
	}
}

bool BossMini::OnRectCollided(Object* object, CollisionSide side)
{
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
		this->vy = 0;
		break;
	default:
		break;
	}
	if (object->tag == Tag::PLAYER)
	{
		return true;
	}
	return false;
	//if()
}

