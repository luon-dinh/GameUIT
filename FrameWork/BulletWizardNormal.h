#pragma once
#include "Bullet.h"

class BulletWizardNormal : public Bullet
{
public:
	BulletWizardNormal()
	{
		this->animation = new Animation(Tag::BOSSWIZARDBULLET, 3, 6);
		this->tag = Tag::BOSSWIZARDBULLET;
	}
	~BulletWizardNormal()
	{
		
	}

	void Update(float dt)override {
		if (this->animation == animationExplode && animation->curframeindex == animation->toframe - 1)
			DeactivateObjectInGrid();
		if (this->direction == Player::MoveDirection::RightToLeft)
			this->vx = ENEMY_BULLET_SPEED * -1;
		else
		{
			this->vx = ENEMY_BULLET_SPEED;
		}
		this->pos.x += this->vx;
		this->pos.y += this->vy;
		animation->Update(dt);
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{
		if (object->tag == this->tag)
			return;
		switch (object->type)
		{
		case Type::SOLIDBOX:
		case Type::GROUND:
			this->animation = animationExplode;
			this->pos.x -= this->vx;
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
 				this->pos.x -= this->vx;
				this->vx = this->vy = 0;
			}
		}
	}

	BoundingBox getBoundingBox()override
	{
		BoundingBox box;
		box.vx = this->vx;
		box.vy = this->vy;
		box.top = this->pos.y + 3;
		box.left = this->pos.y - 3;
		box.right = this->pos.x + 4;
		box.left = this->pos.x - 4;
		return box;
	}
};