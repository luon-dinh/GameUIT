#pragma once
#include "Bullet.h"
#include"Equation.h"

class BulletMiniSpecial : public Bullet
{

public:
	Equation *parapol;
	Animation* anim = new Animation(Tag::BOSSMINIBULLET, 0, 1);
	BulletMiniSpecial(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2)
	{
		this->tag = Tag::BOSSMINIBULLET;
		this->animation = anim;
		parapol = new Equation(pos1, pos2);
	}
	~BulletMiniSpecial()
	{

	}

	void Update(float dt)override {
		if (animation->curframeindex == animationExplode->toframe-1)
			DeactivateObjectInGrid();
		animation->Update(dt);
		this->pos.x += this->vx;
		this->pos.y = parapol->GetYFromX(this->pos.x);
	}

	int GetCollisionDamage()override
	{
		return 6;
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{

	}

	bool OnRectCollided(Object* object, CollisionSide side)override
	{
		return true;
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