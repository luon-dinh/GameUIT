#pragma once
#include "Enemy.h"
#include <unordered_map>
#include "Player.h"
using namespace std;

class EvilBat : public Enemy, public GameObjectProperty {
protected:
	enum BatState {
		OnNeck,
		BelowGround,
		Fly,
		Dead
	};

	unordered_map<BatState, Animation*> animations;

	D3DXVECTOR2 initialPos;
	
	int movingDelayFrame;
	bool activeAnimation;
	bool activeFly;
	bool isWakenUp;
	int moveFlag;
	int preMoveFlag;
	bool isFlyDown;
	int leftX;
	int rightX;
	int edgeY;

	int turnAroundCount;
	int prepareFlyCount;
	int flipFrameCount;
	int incollidableFrameCount;
	int explodeFrameCount;
	BatState state;

	virtual void LoadAllAnimations();
	void UpdatePosition();
	void ChangeState(BatState state);

	void CallMove();
	void PrepareToFly();
	void Move1();
	void Move2();
	void Move3();
	void StopMoving();
	void Explode();
	virtual bool IsWakenUpBy(Object* object);

	void SetMoveFlag(int value);
	bool IsMoveFlagChanged();


	void InnerRender();

	const int Y_MOVING_LENGTH = 50;
	const int TURN_AROUND_POINT_DENTA = 50;
	const int TURN_AROUND_COUNT = 4;
	const int MOVING_DELAY_FRAME = 60;
	const int PREPARE_TO_FLY_FRAME = 30;
	const int WAKEN_UP_DISTANCE = 100;
	const int FLIP_RENDER_FRAME = 10;
	const int INCOLLIDABLE_FRAME = 90;

public:
	EvilBat(D3DXVECTOR2 position);
	~EvilBat();

	// Set dentaX bay tính sang 2 bên, từ vị trí ban đầu trừ đi leftDentaX đến vị trí ban đầu + rightDentaX
	void SetXWidth(int leftDentaX, int rightDentaX);	
	// Set dentaY mà dơi bay dọc ban đầu
	void SetYHeight(int yHeight);


	void OnCollision(Object* object, collisionOut* colOut) override;
	bool OnRectCollided(Object* object, CollisionSide side) override;
	void Update(float dt) override;
	void Render() override;
	void FlipRender();
	int GetCollisionDamage() override;
	int GetDamage() override;
	void UpdateGameProperty() override {};
	void ResetGameProperty() override;
};
