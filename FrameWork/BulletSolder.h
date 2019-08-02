#pragma once
#include"Bullet.h"
#include"Collision.h"
#include"Player.h"
#include"Shield.h"
class BulletSolder:public Bullet {
public:
	BulletSolder(MoveDirection direction)
	{
		this->animation = new Animation(Tag::BLUESOLDERBULLET, 0);
		this->tag = Tag::BLUESOLDERBULLET;
		this->isActive = false;
		this->vy = 0;
		this->existTime = 0;
		this->direction = direction;
		if (this->direction == MoveDirection::RightToLeft)
			this->vx = ENEMY_BULLET_SPEED * -2;
		else
		{
			this->vx = ENEMY_BULLET_SPEED * 2;
		}
	}
	void Update(float dt) override
	{
		if (animation->curframeindex ==animationExplode->toframe-1&&animation==animationExplode)
			DeactivateObjectInGrid();
		this->pos.x += this->vx;
		this->pos.y += this->vy;
		animation->Update(dt);
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{
		auto player = Player::getInstance();
		auto shield = Shield::getInstance();
		float posToShhield = abs(this->pos.x - shield->pos.x);
		float posToPlayer = abs(this->pos.x - player->pos.x);
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
				if (player->hasShield&&shield->state==Shield::ShieldState::Defense&&player->direction!=this->direction && (posToShhield < posToPlayer))
				{
					this->vy = abs(this->vx);
					this->vx = 0;
					return;
				}
				this->animation = animationExplode;
				this->isCollidable=false;
				this->pos.x += this->vx;
				this->vx = this->vy = 0;
			}
		}
		
	}
	
	int GetCollisionDamage()
	{
		return 1;
	}

	bool OnRectCollided(Object* object, CollisionSide side)override
	{
		auto player = Player::getInstance();
		auto shield = Shield::getInstance();
		float posToShhield = abs(this->pos.x - shield->pos.x);
		float posToPlayer = abs(this->pos.x - player->pos.x);
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
				if (player->hasShield&&shield->state == Shield::ShieldState::Defense&&player->direction != this->direction&&(posToShhield<posToPlayer))
				{
					this->vy = abs(this->vx);
					this->vx = 0;
					return true;
				}
				this->animation = animationExplode;
				this->isCollidable = false;
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