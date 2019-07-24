#include "Enemy.h"
#include"Camera.h"
Enemy::Enemy()
{

}

Enemy::~Enemy() {

}


void Enemy::Update(float dt)
{
	this->curentAnimation->Update(dt);
}

void Enemy::Render()
{
	if (!isDead)
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (this->direction)
		{
		case Player::MoveDirection::LeftToRight:
			this->curentAnimation->Render(D3DXVECTOR2(this->pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			this->curentAnimation->Render(this->pos);
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