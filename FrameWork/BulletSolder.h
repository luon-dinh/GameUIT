#pragma once
#include"Bullet.h"
#include"Collision.h"
#include"Player.h"
#include"Shield.h"
class BulletSolder:public Bullet {
public:
	float bulletSpeedx = 2;
	/*bool CanGetThroughShield() override
	{
		return true;
	}*/

	BulletSolder(MoveDirection direction)
	{
		this->animation = new Animation(Tag::BLUESOLDERBULLET, 0);
		this->tag = Tag::BLUESOLDERBULLET;
		this->isActive = false;
		this->vy = 0;
		this->existTime = 0;
		this->direction = direction;
		if (this->direction == MoveDirection::RightToLeft)
			this->vx = -bulletSpeedx;
		else
		{
			this->vx = bulletSpeedx;
		}
	}
	void Update(float dt) override
	{
		this->pos.x += this->vx;
		this->pos.y += this->vy;
		animation->Update(dt);
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{
		/*auto player = Player::getInstance();
		auto shield = Shield::getInstance();
		float posToShhield = abs(this->pos.x - shield->pos.x);
		float posToPlayer = abs(this->pos.x - player->pos.x);
		if (object->tag == Tag::PLAYER)
		{
			if (player->hasShield&&shield->state == Shield::ShieldState::Defense&&player->direction != this->direction && (posToShhield < posToPlayer))
			{
				this->vy = abs(this->vx);
				this->isCollidable = false;
				SoundManager::getinstance()->play(SoundManager::SoundName::shield_collision);
				this->vx = 0;
				return;
			}
			DeactivateObjectInGrid();
			return;
		}
*/
		
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
		if (object->tag == Tag::PLAYER)
		{
			bool collide = Collision::getInstance()->IsCollide(shield->getBoundingBox(), this->getBoundingBox());
			if (player->hasShield&&shield->state == Shield::ShieldState::Defense&&player->direction != this->direction && (posToShhield < posToPlayer)&&collide)
			{
				this->vy = abs(this->vx);
				this->isCollidable = false;
				SoundManager::getinstance()->play(SoundManager::SoundName::shield_collision);
				this->vx = 0;
				return true;
			}
			//this->animation = animationExplode;
			DeactivateObjectInGrid();
			return true;
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