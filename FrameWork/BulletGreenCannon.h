#pragma once
#include"Bullet.h"
#include"Collision.h"
class BulletGreenCannon :public Bullet {
public:
	BulletGreenCannon()
	{
		this->animation = new Animation(Tag::BLUESOLDERBULLET, 0);
		this->isActive = false;
		this->vy = 0;
		this->existTime = 0;
		this->vx = ENEMY_BULLET_SPEED;
	}
	void Update(float dt) override
	{
		if (!this->GetActive())//nếu không active không update
			return;

		if (this->direction == Player::MoveDirection::RightToLeft)
			this->vx = ENEMY_BULLET_SPEED * -1;
		else
		{
			this->vx = ENEMY_BULLET_SPEED;
		}
		this->pos.x += this->vx;
		this->pos.y += this->vy;
		if (existTime >= ENEMY_BULLET_EXIST_TIME)
		{
			this->SetActive(false);
			existTime = 0;
		}
		else
		{
			existTime += dt;
		}
	}

	void OnCollision(Object* object, collisionOut* colOut)override
	{


	}
};