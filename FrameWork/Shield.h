#pragma once
#include "Object.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "Player.h"

class Shield : public Object
{

private:
	static Shield* instance;
	//std::vector<Sprite*>sprites;//chứa danh sách các sprite của shield
	Animation * animation;

	int round;
	D3DXVECTOR2 accelerator;

	const float SHIELD_INITIAL_SPEED = 3;


public:
	enum ShieldDirection {
		LeftToRight,
		RightToLeft
	};

	enum ShieldState {
		Defense,
		Attack,
		Transparent
	};

	ShieldState state;
	ShieldDirection direction;


	static Shield* getInstance();
	void Update(float dt);
	void Render();
	void InputHandler(float dt);
	void OnCollision(Object* object, collisionOut out);
	void setFrameIndex(int index);
	BOOL GetShieldToPlayer();
	void ReverseMoveDirection();
	void MoveAttack();
	void SetShieldState(ShieldState state);
	Shield();
	~Shield();
};

