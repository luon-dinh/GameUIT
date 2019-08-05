#pragma once
#include "Bullet.h"

class BulletWizardSpecial : public Bullet
{
	
public:
	Animation* animation1 = new Animation(Tag::BOSSWIZARDBULLET, 0, 1);
	Animation* animation2 = new Animation(Tag::BOSSWIZARDBULLET, 1, 2);
	Animation* animation3 = new Animation(Tag::BOSSWIZARDBULLET, 2, 3);

	bool CanGetThroughShield() override
	{
		return true;
	}

	BulletWizardSpecial()
	{
		//this->animation->curframeindex = 2;
		this->tag = Tag::BOSSWIZARDBULLET;
	}
	~BulletWizardSpecial()
	{

	}

	void Update(float dt)override {
		animation->Update(dt);
		this->pos.x += this->vx;
		this->pos.y += this->vy;
	}

	int GetCollisionDamage()
	{
		return 3;
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{
		if (object->tag == Tag::PLAYER)
		{
			this->isCollidable = false;
			return;
		}
	}

	bool OnRectCollided(Object* object, CollisionSide side)
	{
		if (object->tag == Tag::PLAYER)
		{
			this->isCollidable = false;
			return true;
		}
		return false;
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

	//void Render()override
	//{
	//	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	//	if(animation->curframeindex==0)
	//		
	//}
};