#include "Enemy.h"
#include"Camera.h"
Enemy::Enemy()
{
	explode = new Animation(Tag::ENEMYEXPLODE, 0, 3, delaySpriteExplode);
}

Enemy::~Enemy() {
	if (explode != nullptr)
		delete explode;
}


void Enemy::Update(float dt)
{
	this->currentAnimation->Update(dt);
}

void Enemy::Render()
{
	if (!isDead)
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (this->direction)
		{
		case Player::MoveDirection::LeftToRight:
			this->currentAnimation->Render(D3DXVECTOR2(this->pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			this->currentAnimation->Render(this->pos);
			break;
		default:
			break;
		}
	}
}

void Enemy::Respawn()
{
	isDead = false;
}