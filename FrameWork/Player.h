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
#include "PlayerClimbingState.h"
#include "PlayerBeatenState.h"
#include "PlayerFlyingBeatenState.h"
#include "PlayerDyingState.h"
#include "Object.h"
#include "Collision.h"
#include "GroundCollision.h"
#include "SolidBoxCollision.h"
#include "GamePlayerProperty.h"
#include "HealthPoint.h"
#include "Bullet.h"
#include "BulletGreenCannon.h"
#include "BulletRedRocket.h"
#include "BulletRedRocketLinear.h"
#include "BulletRedRocketNonLinear.h"
#include "PlayerHandPunch.h"
#include "PlayerKickPart.h"


class Player :public Object, public GamePlayerProperty
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

	void InnerRender();
	
	int flipRenderFrame;
	const int FLIP_RENDER_FRAME = 10;

	const int MIN_TIME_JUMP_1 = 20;
	const int MIN_TIME_JUMP_2 = 30;
	const int MIN_TIME_ROLL = 40;
	const int MAX_TIME_JUMP = 50;
	const float ADDED_SPEED_1 = 0.09;
	const float ADDED_SPEED_2 = 0.14;
	
public:

	bool shieldActive;
	BOOL hasShield;
	bool canDash = true;
	enum ShieldReturnEdge {
		Top,
		Left,
		Bottom,
		Right,
		Default		//	 Sử dụng tọa độ của player
	};

	//	std::list<Object*> collideObject;	//danh sach cac object va cham voi player
	float getWidth();
	float getHeight();
	void ChangeState(PlayerState* newplayerstate);
	void ChangeState(State stateName) override;
	void Update(float dt);
	float getPosToBotom();
	void Render();
	void RenderInGrid() {}; //Cấm không cho player render trong Grid.
	PlayerState* GetPreviousState();
	void SetPreviousState(State stateName);
	BoundingBox getBoundingBox();
	State state;
	Type type;
	static Player* getInstance();
	Animation * curanimation;
	PlayerState * playerstate;
	ShieldReturnEdge edge;

	D3DXVECTOR2 shieldReturnPos;

	Player();
	~Player();


#pragma region MyRegion
	void SetVx(float vx, BOOL changePlayerDirection);
	void SetVx(float vx) override;
	void SetCollisionAffect(BOOL value);
	BOOL GetCollisionAffect();
	virtual void UpdatePosition()				 override;
	void SetOnAirState(OnAir onAirState)         override;
	void SetMoveDirection(MoveDirection moveDir) override;
	int GetDamage()								 override;
	bool IsNonAttackable()						 override;
	bool IsImmortal()						     override;
	BOOL IsReachMaxJump();
	bool IsOnPlatform();
	
	void OnHeadOnSolidBox(Object* solid);
	bool AcceptNoCollision(Object* object, CollisionSide side);

	void Float(MoveDirection moveDir);

	void SetShieldReturnEdge(ShieldReturnEdge edge);
	ShieldReturnEdge GetShieldReturnEdge();
	D3DXVECTOR2 GetShieldReturnPos();

	bool IsFootStepOn();
	int GetCollisionDamage() override;




#pragma endregion

#pragma region Player Collision Handle

	bool TryStandOnGround(Object* ground);

	void DeactivateObjectInGrid()override {};

	void OnJumping(int frames);
	void OnCollision(Object* object, collisionOut* collisionOut)		 override;
	void OnNotCollision(Object* object)									 override;
	bool OnRectCollided(Object* object, CollisionSide side)				 override;
	void OnFallingOffGround()											 override;
	void OnSmashSolidBox(Object* solid, CollisionSide side)				 override;
	void OnClimbingTheRope(Object* rope);

	void OnCollisionWithEnemy(Object* enemy);
	void OnCollisionWithBullet(Bullet* bullet);

#pragma endregion


};

