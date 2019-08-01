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
		if (animation->curframeindex == 2)
			DeactivateObjectInGrid();
		animation->Update(dt);
		this->pos.x += this->vx;
		this->pos.y += this->vy;
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