#pragma once
#include"Bullet.h"
#include"Collision.h"
class BulletSolder:public Bullet {
public:
	BulletSolder()
	{
		this->animation = new Animation(Tag::BLUESOLDERBULLET, 0);
		this->isActive = false;
		this->vy = 0;
		this->existTime = 0;
		this->vx = ENEMY_BULLET_SPEED;
	}
	void Update(float dt) override
	{
		if (this->direction == Player::MoveDirection::RightToLeft)
			this->vx = ENEMY_BULLET_SPEED* -1;
		else
		{
			this->vx = ENEMY_BULLET_SPEED;
		}
		this->pos.x += this->vx;
		this->pos.y += this->vy;
		animation->Update(dt);
		if (existTime > ENEMY_BULLET_EXIST_TIME||animation->curframeindex==2)
		{
			existTime = 0;
			DeactivateObjectInGrid();
		}
		else 
		{
			existTime += dt;
		}
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{
		switch (object->type)
		{
		case Type::SOLIDBOX:
		case Type::GROUND:
			this->animation = animationExplode;
			this->pos.x += this->vx;
			this->vx = this->vy = 0;
			break;
		default:
			break;
		}
		if (object->type == Type::NONE)
		{
			if (object->tag == Tag::PLAYER)
			{
				this->animation = animationExplode;
				this->pos.x += this->vx;
				this->vx = this->vy = 0;
			}
		}
	}
	BoundingBox getBoundingBox()override
	{
		BoundingBox box;
		box.vx = this->vx;
		box.vy = this->vy;
		box.left = this->pos.x - 3;
		box.right = this->pos.x + 3;
		box.top = this->pos.y + 3;
		box.bottom = this->pos.y - 3;
		return box;
	}
	~BulletSolder()
	{
		
	}
};