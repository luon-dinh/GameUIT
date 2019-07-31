#include "Enemy.h"
#include"Camera.h"
Enemy::Enemy()
{
	explodeAnim = new Animation(Tag::ENEMYEXPLODE, 0, 3, delaySpriteExplode);
	this->type = Type::ENEMY;
}

Enemy::~Enemy() {
	if (explodeAnim != nullptr)
		delete explodeAnim;
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
			this->currentAnimation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			this->currentAnimation->Render(pos);
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