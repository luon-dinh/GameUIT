#pragma once
#include "Enemy.h"


class EvilBat : public Enemy, public GameObjectProperty {
protected:
	enum BatState {
		OnNeck,
		BelowGround,
		Fly,
		Dead
	};

	Animation* fakeContainerAnim;
	Animation* belowGroundAnim;
	Animation* flyAnim;
	D3DXVECTOR2 initialPos;
	
	bool activeAnimation;
	bool moveFlag;
	bool preMoveFlag;
	bool isFlyDown;
	int leftX;
	int rightX;
	int edgeY;
	int turnAroundCount;
	BatState state;

	void LoadAllAnimations();
	void UpdatePosition();
	void ChangeState(BatState state);

	void CallMove();
	void Move1();
	void Move2();
	void Move3();
	void StopMoving();

	void(EvilBat::*curentMoveHandler)();

	void SetMoveFlag(bool value);
	bool IsMoveFlagChanged();



	const int Y_MOVING_LENGTH = 50;
	const int TURN_AROUND_POINT_DENTA = 50;
	const int TURN_AROUND_COUNT = 4;

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
	int GetCollisionDamage() override;
	int GetDamage() override;
	void UpdateGameProperty() override;
	void ResetGameProperty() override;
};
