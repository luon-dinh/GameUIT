#pragma once
#include "Bullet.h"

class BulletMiniNormal : public Bullet
{

public:
	Animation* anim = new Animation(Tag::BOSSMINIBULLET, 1, 2);

	bool CanGetThroughShield() override
	{
		return true;
	}

	BulletMiniNormal()
	{
		this->tag = Tag::BOSSMINIBULLET;
		this->animation = anim;
	}
	~BulletMiniNormal()
	{

	}

	void Update(float dt)override {
		if (animation->curframeindex == animationExplode->toframe-1)
			DeactivateObjectInGrid();
		animation->Update(dt);
		this->pos.x += this->vx;
		this->pos.y += this->vy;
	}

	int GetCollisionDamage()override
	{
		return 2;
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{
		
	}

	bool OnRectCollided(Object* object, CollisionSide side)override
	{
		switch (object->type)
		{
		case Type::GROUND:
		case Type::SOLIDBOX:
			this->animation = animationExplode;
			this->vx = this->vy = 0;
			return false;
		default:
			break;
		}
		if (object->tag == Tag::PLAYER)
		{
			this->animation = animationExplode;
			this->vx = this->vy = 0;
			return true;
		}
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