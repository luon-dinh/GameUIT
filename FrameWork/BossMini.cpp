#include"BossMini.h"

BossMini::BossMini()
{
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
	float deltaX = this->pos.x - player->pos.x;
	if (deltaX > 0)
		this->direction = MoveDirection::RightToLeft;
	else
	{
		this->direction = MoveDirection::LeftToRight;
	}
}

BossMini::~BossMini()
{

}

void BossMini::LoadAllAnimations()
{
	animations[State::FALLING] = new Animation(Tag::BOSSMINIBULLET, 0, 1);
	animations[State::STANDING] = new Animation(Tag::BOSSMINIBULLET, 1, 2);
	animations[State::ATTACKING_FLY] = new Animation(Tag::BOSSMINIBULLET, 2, 4);
	animations[State::ATTACK] = new Animation(Tag::BOSSMINIBULLET, 4, 5);
	animations[State::RUNNING] = new Animation(Tag::BOSSMINIBULLET, 5, 8);
	animations[State::BEATEN] = new Animation(Tag::BOSSMINIBULLET, 8, 10);
	animations[State::DEAD] = new Animation(Tag::BOSSMINIBULLET, 10, 11);
	animations[State::DASHING] = new Animation(Tag::BOSSMINIBULLET, 10, 11);
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

void BossMini::Update(float dt)
{
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	this->currentAnimation->Update(dt);
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
	this->state = stateName;
	this->currentAnimation = animations[stateName];
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
	return false;
	//if()
}

