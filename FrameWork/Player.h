#pragma once
#include"SoundManager.h"
#include"KeyboardManager.h"
#include"PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "PlayerJumpingState.h"
#include "PlayerSittingState.h"
#include "PlayerDuckingPunchingState.h"
#include "PlayerKickingState.h"
#include "PlayerShieldUpState.h"
#include "PlayerRollingState.h"
#include "PlayerDashingState.h"
#include "PlayerFloatingState.h"
#include "Object.h"
#include "Collision.h"
#include "GroundCollision.h"


class Player :public Object
{
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua player
	std::unordered_map<State, PlayerState*> playerStates;
	static Player* instance;

	PlayerState
		*runningState,
		*standingState,
		*jumpingState,
		*sittingState,
		*floatingState;

	void InnerChangeState(State stateName);
	void LoadAllStates();
	void LoadAllAnimations();
	void AddPosX();
	void AddPosY();

	PlayerState* prevState;

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
		DropToWater,
		None
	};

	//	std::list<Object*> collideObject;	//danh sach cac object va cham voi player
	int getWidth();
	int getHeight();
	void ChangeState(PlayerState* newplayerstate);
	void ChangeState(State stateName);
	void Update(float dt);
	virtual void OnCollision(Object* object, collisionOut* collisionOut);
	void Render();
	PlayerState* GetPreviousState();
	void SetPreviousState(State stateName);
	BoundingBox getBoundingBox();
	State state;
	MoveDirection direction;
	Type type;
	static Player* getInstance();
	Animation * curanimation;
	PlayerState * playerstate;
	OnAir onAirState;
	D3DXVECTOR2 accelerate;
	BOOL collideOnGround;

	GroundCollision* groundCollision;

	Player();
	~Player();
	

#pragma region MyRegion
	void SetVx(float vx);
	void SetVy(float vy);
	void SetVelocity(D3DXVECTOR2 veloc);
	void SetAccelerate(D3DXVECTOR2 acclerate);
	virtual void UpdatePosition();
	void SetAirState(OnAir onAirState);
	void SetMoveDirection(MoveDirection moveDir);
	OnAir GetOnAirState();
	BOOL IsReachMaxJump();
	void SetGroundCollision(GroundCollision* groundCollision);
	GroundCollision* GetGroundCollision();
#pragma endregion

};

