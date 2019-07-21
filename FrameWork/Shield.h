#pragma once
#include "Object.h"
#include"TextureManager.h"
#include"SpriteManager.h"
#include"Player.h"
#include "ShieldState.h"
#include <unordered_map>
#include "ShieldDownState.h"
#include "ShieldUpState.h"
#include "ShieldNormalState.h"
#include "ShieldJumpState.h"
#include "ShieldAttackState.h"

using namespace std;

class Shield :
	public Object
{
private:
	static Shield* instance;
	//std::vector<Sprite*>sprites;//chứa danh sách các sprite của shield
	Animation * animation;


	const float SHIELD_MOVE_ACCELERATOR = 0.3;
	const float SHIELD_INITIAL_SPEED = 3;

	D3DXVECTOR2 accelerator;

	enum MoveDirection {
		LeftToRight,
		RightToLeft
	};

	MoveDirection direction;
	int round;



	void ReverseShieldDirection();
	BOOL GetShieldToPlayer();

	const int NUMBER_SPRITES = 6;
public:

	enum State {
		ShieldUp,
		ShieldDown,
		ShieldJump,
		ShieldNormal,
		ShieldRun,
		ShieldAttack,
		None			// không render
	};

	enum ShieldDirection {
		LeftToRight,
		RightToLeft
	};

	unordered_map<Shield::State, ShieldState*> shieldStates;
	ShieldState* state;
	ShieldDirection direction;

	static Shield* getInstance();
	void Update(float dt);
	void Render();
	void InputHandler(float dt);
	void OnCollision(Object* object, collisionOut out);
	void setFrameIndex(int index);
	void MoveAttack();

	Shield();
	~Shield();

	void ChangeState(Shield::State state);

	void LoadAllStates();
};

