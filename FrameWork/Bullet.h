#pragma once
#include"Object.h"
#include"Camera.h"
#include"SoundManager.h"
class Bullet:public Object {
public:
	float speed;
	Animation* animation;
	Animation* animationExplode;
	float existTime;
	//Thời gian để sau khi nổ thì đạn biến mất.
	const int delayDisappear = 300;
	//Delay phục vụ cho việc xoá object khỏi grid khi nổ tung hoàn thành.
	float curDelayTime = 0;
	Bullet()
	{
		animationExplode = new Animation(Tag::BULLETEXPLODE, 0, 3, TIME_PER_FRAME/3);
		this->tag = Tag::BULLET;
		this->type = Type::BULLETTYPE;
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
		{
			SoundManager::getinstance()->play(SoundManager::SoundName::object_explode);
			DeactivateObjectInGrid();
		}
	}

	virtual void Render()
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (direction) {
		case MoveDirection::LeftToRight:
			this->animation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
			break;
		case MoveDirection::RightToLeft:
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
	virtual int GetBulletDamage() { return 0; }
	virtual bool CanGetThroughShield() { return false; }
};