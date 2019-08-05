#pragma once
#include "Bullet.h"
#include"Equation.h"

class BulletWizardNormal : public Bullet
{
	
public:
	
	Animation* animation1 = new Animation(Tag::BOSSWIZARDBULLET, 3, 4);
	Animation* animation2 = new Animation(Tag::BOSSWIZARDBULLET, 4, 5);
	Animation* animation3 = new Animation(Tag::BOSSWIZARDBULLET, 5, 6);
	Equation* parapol=NULL;
	/*bool CanGetThroughShield() override
	{
		return true;
	}
*/
	BulletWizardNormal()
	{
		this->tag = Tag::BOSSWIZARDBULLET;
	}
	~BulletWizardNormal()
	{
		
	}

	void Update(float dt)override {
		animation->Update(dt);
		if (parapol != NULL)
		{
			this->vy = (this->parapol->GetYFromX(this->pos.x + this->vx) - this->parapol->GetYFromX(this->pos.x));
			if (vy < -3)
				this->vx *= 0.9;
			this->pos.x += this->vx;

			this->pos.y = this->parapol->GetYFromX(this->pos.x);
		}
		else
		{
			this->pos.x += this->vx;
			this->pos.y += this->vy;
		}
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{
	
		/*auto player = Player::getInstance();
		auto shield = Shield::getInstance();
		float posToShhield = abs(this->pos.x - shield->pos.x);
		float posToPlayer = abs(this->pos.x - player->pos.x);
		if (object->type == Type::NONE)
		{
			if (object->tag == Tag::PLAYER)
			{
				this->isCollidable = false;
				if (player->hasShield&&shield->state == Shield::ShieldState::Defense&&player->direction != this->direction && (posToShhield < posToPlayer))
				{
					this->vy = -abs(this->vx);
					this->vx = 0;
					return;
				}
			
			}
		}*/
	
	}

	bool OnRectCollided(Object* object, CollisionSide side)override
	{
		
		auto player = Player::getInstance();
		auto shield = Shield::getInstance();
		float posToShhield = abs(this->pos.x - shield->pos.x);
		float posToPlayer = abs(this->pos.x - player->pos.x);
		if (object->tag == Tag::PLAYER)
		{
			this->isCollidable = false;
			SoundManager::getinstance()->play(SoundManager::SoundName::shield_collision);
			if (player->hasShield&&shield->state == Shield::ShieldState::Defense&&player->direction != this->direction && (posToShhield < posToPlayer))
			{
				D3DXVECTOR2 pos1;
				D3DXVECTOR2 pos2;
				pos1.y = shield->pos.y;
				pos2.y = shield->pos.y+3;
				if (this->direction == MoveDirection::LeftToRight)
				{
					pos1.x = shield->pos.x + 4;
					pos2.x = pos1.x - 10;
				}
				else
				{
					pos1.x = shield->pos.x - 4;
					pos2.x = pos1.x + 10;
				}
				this->vx = -this->vx/3;
				this->parapol = new Equation(pos1, pos2);
				return true;
			}

			return true;
		}
		return false;
	}

	int GetCollisionDamage()
	{
		return 5;
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