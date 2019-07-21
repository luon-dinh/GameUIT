#pragma once
#include "Object.h"
#include"TextureManager.h"
#include"SpriteManager.h"
#include"Player.h"
class Shield :
	public Object
{
private:
	static Shield* instance;
	//std::vector<Sprite*>sprites;//chứa danh sách các sprite của shield
	Animation * animation;

	const float SHIELD_INITIAL_SPEED = 3;
	D3DXVECTOR2 accelerator;
	int round;
public:
	Player::MoveDirection direction;
	enum ShieldState {

	};
	static Shield* getInstance();
	void Update(float dt);
	void Render();
	void InputHandler(float dt);
	void OnCollision(Object* object, collisionOut out);
	void setFrameIndex(int index);
	Shield();
	~Shield();

	void ReverseShieldDirection();
	void MoveAttack();
	BOOL GetShieldToPlayer();
};

