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
#include "PlayerDivingState.h"
#include "PlayerStandPunchState.h"
#include "PlayerShieldDownState.h"
#include "PlayerShieldAttackState.h"
#include "Object.h"
#include "Collision.h"
#include "GroundCollision.h"
#include "SolidBoxCollision.h"
#include "Shield.h"


class Player :public Object
{
private:
	std::unordered_map<State, Animation *>animations; //cac animation cua player
	std::unordered_map<State, PlayerState*> playerStates;
	static Player* instance;


	void InnerChangeState(State stateName);
	void LoadAllStates();
	void LoadAllAnimations();
	void AddPosX();
	void AddPosY();

	BOOL collisionAffect;

	PlayerState* prevState;

public:
	int health;
	int live;
	int energy;
	bool hasShield;

	enum MoveDirection {
		LeftToRight,
		RightToLeft,
	};

	enum OnAir {
		Jumping,
		Falling,
		DropToWater,
		None,
		JumpFromWater
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
	OnAir preOnAir;
	D3DXVECTOR2 accelerate;
	BOOL collideOnGround;


	GroundCollision* groundCollision;
	SolidBoxCollision* solidBoxCollision;

	Player();
	~Player();
	

#pragma region MyRegion
	void SetVx(float vx);
	void SetVx(float vx, BOOL changePlayerDirection);
	void SetVy(float vy);
	void SetVelocity(D3DXVECTOR2 veloc);
	void SetAccelerate(D3DXVECTOR2 acclerate);
	void SetCollisionAffect(BOOL value);
	BOOL GetCollisionAffect();
	virtual void UpdatePosition();
	void SetAirState(OnAir onAirState);
	void SetMoveDirection(MoveDirection moveDir);
	OnAir GetOnAirState();
	OnAir GetPreOnAirState();
	BOOL IsReachMaxJump();

	void Float(MoveDirection moveDir);
	void HandleWaterCollision(Object* water, collisionOut* side);
	BOOL IsOnMainGround();
#pragma endregion

#pragma region Player Collision Handle
	void SetGroundCollision(GroundCollision* groundCollision);
	GroundCollision* GetGroundCollision();
	void SetSolidBoxCollision(SolidBoxCollision* solidBoxCollision);
	SolidBoxCollision* GetSolidBoxCollision();
	
	BOOL CollideWithSolidBox(Object* solidBox);

	void HandleFallingOffGround();					// xử lý khi rơi khỏi ground
	void HandleStandingOnGround(Object* ground);	// xử lý khi đứng trên ground
	void HandleCollisionWithSolidBox(Object* solidBox);
#pragma endregion


};

