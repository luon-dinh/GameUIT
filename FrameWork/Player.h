#pragma once
#include"SoundManager.h"
#include"KeyboardManager.h"
#include"PlayerState.h"
#include"PlayerStandingState.h"
#include"Object.h"

class Player :public Object
{
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua player
	static Player* instance;
public:
	int health;
	int live;
	int energy;

	//	std::list<Object*> collideObject;	//danh sach cac object va cham voi player

	void ChangeState(PlayerState* newplayerstate);
	void Update(float dt);
	void Render();
	void KeyDown();
	State state;
	Type type;
	static Player* getInstance();
	Animation * curanimation;
	PlayerState * playerstate;

	Player();
	~Player();
};

