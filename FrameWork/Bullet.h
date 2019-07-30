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
	//Thời gian để sau khi nổ thì đạn biến mất.
	const int delayDisappear = 300;
	//Delay phục vụ cho việc xoá object khỏi grid khi nổ tung hoàn thành.
	float curDelayTime = 0;
	Bullet()
	{
		animationExplode = new Animation(Tag::BULLETEXPLODE, 0, 3, TIME_PER_FRAME/3);
	}
	~Bullet()
	{

	}
	virtual void Update(float dt)
	{
		this->pos.x += this->vx;
		this->pos.y += this->vy;
	};

	virtual void UpdateOnExploded(float dt)
	{
		curDelayTime += dt;
		this->animation->Update(dt);
		if (curDelayTime > delayDisappear)
			DeactivateObjectInGrid();
	}

	virtual void Render()
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (direction) {
		case Player::MoveDirection::LeftToRight:
			this->animation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			this->animation->Render(pos);
			break;
		default:
			break;
		}
	};
	int RenderWeight() override
	{
		return RenderWeightOfObjects::BULLET_RENDER_WEIGHT;
	}
	virtual void OnCollision(Object* object, collisionOut* colOut)
	{

	}
};