#pragma once
#include "Bullet.h"

class BulletWizardNormal : public Bullet
{
	
public:
	
	Animation* animation1 = new Animation(Tag::BOSSWIZARDBULLET, 3, 4);
	Animation* animation2 = new Animation(Tag::BOSSWIZARDBULLET, 4, 5);
	Animation* animation3 = new Animation(Tag::BOSSWIZARDBULLET, 5, 6);
	BulletWizardNormal()
	{
		this->tag = Tag::BOSSWIZARDBULLET;
	}
	~BulletWizardNormal()
	{
		
	}

	void Update(float dt)override {
		if (animation->curframeindex == this->animationExplode->toframe-1)
			DeactivateObjectInGrid();
		animation->Update(dt);
		this->pos.x += this->vx;
		this->pos.y += this->vy;
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
				if (player->hasShield&&shield->state == Shield::ShieldState::Defense&&player->direction != this->direction && (posToShhield < posToPlayer))
				{
					this->vy = -abs(this->vx);
					this->vx = 0;
					this->isCollidable = false;
					return;
				}
				this->animation = animationExplode;
				this->isCollidable = false;
				this->pos.x += this->vx;
				this->vx = this->vy = 0;
			}
		}
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
				if (player->hasShield&&shield->state == Shield::ShieldState::Defense&&player->direction != this->direction && (posToShhield < posToPlayer))
				{
					this->vy = -abs(this->vx);
					this->vx = 0;
					this->isCollidable = false;
					return true;
				}
				this->animation = animationExplode;
				this->isCollidable = false;
				this->pos.x += this->vx;
				this->vx = this->vy = 0;
				return true;
			}
		}
		return false;
	}

	int GetCollisionDamage()
	{
		return 2;
	}

	BoundingBox getBoundingBox()override
	{
		BoundingBox box;
		box.vx = this->vx;
		box.vy = this->vy;
		auto sprite = this->animation->getSprite(this->animation->curframeindex);
		RECT rect = sprite->getRECT();
		height = rect.top - rect.bottom;
		width = rect.right - rect.left;
		box.top = this->pos.y + height / 2;
		box.bottom = this->pos.y - height / 2;
		box.left = this->pos.x - width / 2;
		box.right = this->pos.x + width / 2;
		return box;
	}
};