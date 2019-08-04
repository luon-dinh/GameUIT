#pragma once
#include "Object.h"
#include"Player.h"


class Enemy : public Object {
protected:
	const int delaySpriteExplode = 60;
	//Thời gian trình chiếu animation nổ tung.
	const int explodeTime = 200;
	//Thời gian delay giữa hai lần chớp chớp.
	const int delayBeatenSprite = 50;
public:
	enum DamageEffect {
		Normal,
		Eletric
	};
	Enemy();
	~Enemy();
	float speed;
	bool isDead;
	DamageEffect damageEffect;

	//Máu của quái.
	//Phải set lại trong constructor của từng quái khác nhau.
	double health = 0;

	MoveDirection direction;
	Animation* currentAnimation;
	Animation* explodeAnim;

	//Hàm update tương ứng với từng trạng thái của enemy.
	virtual void EnemyAliveUpdate(double dt) {};
	virtual void EnemyBeatenUpdate(double dt) {};
	virtual void EnemyDeadUpdate(double dt) {} ;
	virtual void ChangeState(State) {};

	virtual void OnCollision(Object* object, collisionOut* colOut) override{};
	bool OnRectCollided(Object* object, CollisionSide side)override { return false; };
	void OnNotCollision(Object* object)override {};
	virtual void Update(float dt);
	virtual void Render();
	virtual void Respawn();

	int RenderWeight() override
	{
		return RenderWeightOfObjects::ENEMY_RENDER_WEIGHT;
	}

	virtual DamageEffect GetDamageEffect();
};