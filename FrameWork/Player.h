#pragma once
#include "Shield.h"
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
	void SetShieldReturnPos(float x, float y);

	BOOL collisionAffect;

	PlayerState* prevState;

public:
	int health;
	int live;
	int energy;
	bool shieldActive;
	BOOL hasShield;

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

	enum ShieldReturnEdge {
		Top,
		Left,
		Bottom,
		Right,
		Default		//	 Sử dụng tọa độ của player
	};

	enum MoveBehavior {
		Normal,
		StoppedByVerticalBoxOnLeft,
		StoppedByVerticalBoxOnRight,
		GoThrough,
	};

	//	std::list<Object*> collideObject;	//danh sach cac object va cham voi player
	int getWidth();
	int getHeight();
	void ChangeState(PlayerState* newplayerstate);
	void ChangeState(State stateName);
	void Update(float dt);

	void Render();
	void RenderInGrid() {}; //Cấm không cho player render trong Grid.
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
	ShieldReturnEdge edge;
	MoveBehavior moveBehave;


	GroundCollision* groundCollision;
	SolidBoxCollision* solidBoxCollision;

	D3DXVECTOR2 shieldReturnPos;
	bool isStateChanged;

	bool smashRight;
	bool smashLeft;
	bool isStopBySolidBox;

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

	BOOL IsOnMainGround();
	void SetShieldReturnEdge(ShieldReturnEdge edge);
	ShieldReturnEdge GetShieldReturnEdge();
	D3DXVECTOR2 GetShieldReturnPos();

	bool StandOnCurrentGround();


	Object* collidedSolidBox;

#pragma endregion

#pragma region Player Collision Handle
	void SetGroundCollision(GroundCollision* groundCollision);
	GroundCollision* GetGroundCollision();

	bool TryStandOnGround(Object* ground);


	void DeactivateObjectInGrid()override {};

	bool IsStopBySolidBox();

	void OnCollision(Object* object, collisionOut* collisionOut);
	void OnNotCollision(Object* object);
	bool OnRectCollided(Object* object, CollisionSide side);
	void OnFallingOffGround();						// xử lý khi rơi khỏi ground
	void OnStandingOnGround(Object* ground);		// xử lý khi đứng trên ground
	void OnCollisionWithSolidBox(Object* solidBox, collisionOut* colOut);
	void OnCollisionWithWater(Object* water, collisionOut* side);
	void OnSmashSolidBox(Object* solid, CollisionSide side);
	void OnHeadOnSolidBox(Object* solid);
	void OnStateChanged(State oldState, State newState);


	bool CanStandOnGround(Object* ground);
	void SetMoveBehavior(MoveBehavior moveBehave);

	void SetCollisionResult(bool value);
	bool collisionResult;

#pragma endregion
};

Player::MoveDirection;

