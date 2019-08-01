#pragma once
#include "Bullet.h"

class BulletWizardSpecial : public Bullet
{
	
public:
	Animation* animation1 = new Animation(Tag::BOSSWIZARDBULLET, 0, 1);
	Animation* animation2 = new Animation(Tag::BOSSWIZARDBULLET, 1, 2);
	Animation* animation3 = new Animation(Tag::BOSSWIZARDBULLET, 2, 3);
	BulletWizardSpecial()
	{
		//this->animation->curframeindex = 2;
		this->tag = Tag::BOSSWIZARDBULLET;
	}
	~BulletWizardSpecial()
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
		box.top = this->pos.y + 4;
		box.left = this->pos.y - 4;
		box.right = this->pos.x + 3;
		box.left = this->pos.x - 3;
		return box;
	}

	//void Render()override
	//{
	//	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	//	if(animation->curframeindex==0)
	//		
	//}
};