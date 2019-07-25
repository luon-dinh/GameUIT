#pragma once
#include"Object.h"
#include"Camera.h"
#include"Player.h"
class Bullet:public Object {
public:
	float speed;
	Animation* animation;
	Animation* animationExplode;
	Player::MoveDirection direction;
	float existTime;

	Bullet()
	{
		animationExplode = new Animation(Tag::BULLETEXPLODE, 0, 3);
	}
	~Bullet()
	{

	}
	virtual void Update(float dt)
	{

	};
	virtual void Render()
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (this->direction) {
		case Player::MoveDirection::LeftToRight:
			animation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			animation->Render(pos);
			break;
		default:
			break;
		}
	};
	virtual void OnCollision(Object* object, collisionOut* colOut)
	{

	}
};