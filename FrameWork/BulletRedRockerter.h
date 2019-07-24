#pragma once
#include"Bullet.h"
#include"Collision.h"
class BulletRedRockerter :public Bullet {
public:
	BulletRedRockerter()
	{
		this->animation = new Animation(Tag::REDROCKERTERBULLET, 0, 4);
		this->isActive = false;
		this->vy = 0;
		this->existTime = 0;
		this->vx = ENEMY_BULLET_SPEED;
		this->vy = ENEMY_BULLET_SPEED;
	}

	void Update(float dt) override
	{
		if (!this->GetActive())
			return;
		if (animation->curframeindex != animation->toframe - 1)
		{
			if (this->direction == Player::MoveDirection::RightToLeft)
				this->vx = ENEMY_BULLET_SPEED* -1;
			else
			{
				this->vx = ENEMY_BULLET_SPEED;
			}
			this->pos.x += this->vx;
			animation->Update(dt);
		}
		else
		{
			if (this->direction == Player::MoveDirection::RightToLeft)
				this->vx = ENEMY_BULLET_SPEED * -1;
			else
			{
				this->vx = ENEMY_BULLET_SPEED;
			}
			this->pos.x += this->vx;
			this->pos.y += this->vy;
		}
		if (existTime >= ENEMY_BULLET_EXIST_TIME)
		{
			this->SetActive(false);
			//delete this;
			existTime = 0;
		}
		else
		{
			existTime += dt;
		}
	}

	void OnCollision(Object* object, collisionOut* colOut) override
	{

	}
};