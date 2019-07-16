#pragma once
#include"SoundManager.h"
#include"KeyboardManager.h"
#include"PlayerStandingState.h"
#include"PlayerRunningState.h"
#include"PlayerFallingState.h"
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
		*fallingState;

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

	Player();
	~Player();


};

