#pragma once
#include"SoundManager.h"
#include"KeyboardManager.h"
#include"PlayerStandingState.h"
#include"PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include"Object.h"
#include "Collision.h"

class Player :public Object
{
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua player
	static Player* instance;

	PlayerState
		*runningState,
		*standingState,
		*jumpingState;

	void InnerChangeState(PlayerState* state);
	void LoadAllStates();

public:
	int health;
	int live;
	int energy;

	enum MoveDirection {
		LeftToRight,
		RightToLeft
	};

	enum OnAir {
		Jumping,
		Falling,
		None
	};

	//	std::list<Object*> collideObject;	//danh sach cac object va cham voi player
	int getWidth();
	int getHeight();
	void ChangeState(PlayerState* newplayerstate);
	void ChangeState(State stateName);
	void Update(float dt);
	void OnCollision(Object* object, collisionOut* collisionOut);
	void Render();
	void KeyDown();

	State state;
	MoveDirection direction;
	Type type;
	static Player* getInstance();
	Animation * curanimation;
	PlayerState * playerstate;
	OnAir onAirState;
	D3DXVECTOR2 accelerate;

	Player();
	~Player();
	

#pragma region MyRegion
	void SetVx(float vx);
	void SetVy(float vy);
	void SetVelocity(D3DXVECTOR2 veloc);
	void SetAccelerate(D3DXVECTOR2 acclerate);
	void AddPosX();
	void AddPosY();
	void AddPos();
	void SetAirState(OnAir onAirState);
	void SetMoveDirection(MoveDirection moveDir);
#pragma endregion

};

