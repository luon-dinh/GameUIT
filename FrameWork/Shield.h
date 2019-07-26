#pragma once
#include "Object.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "Player.h"

class Shield : public Object
{

private:
	static Shield* instance;
	//std::vector<Sprite*>sprites;//chứa danh sách các sprite của shield
	Animation * animation;

	D3DXVECTOR2 accelerator;

	BOOL isActive;

	int numberOfRounds;
	int framePerRound;
	int restFrames;
	BOOL beginRound;
	
	const float SHIELD_INITIAL_SPEED = 12;

public:

	enum ShieldState {
		Defense,
		Attack,
		Transparent,
		NotRender
	};

	enum MoveBehavior {
		FarFromPlayer,
		BackToPlayer,
		NotMove
	};



	ShieldState state;
	MoveBehavior moveBehave;


	static Shield* getInstance();
	void Update(float dt);
	void Render();
	void RenderInGrid() {}; //Cấm không cho Shield render trong grid.
	void InputHandler(float dt);

	void setFrameIndex(int index);
	void SetShieldState(ShieldState state);
	BoundingBox getBoundingBox() override;

	void SetNumberOfRounds(int numberOfRounds);
	void SetFramePerRound(int fpr);
	void Move();
	BOOL MoveOutFromPlayer(int fpr);
	BOOL MoveBackToPlayer(int fpr);

	void UpdatePositionVector();
	void ResetMoveStatus();

	Shield();
	~Shield();

	void DeactivateObjectInGrid() override {};
	void SetMoveDirection(MoveDirection moveDir) override;


	void ChangeState(State stateName) override {};
	void OnCollision(Object* object, collisionOut* out) override;
	void OnNotCollision(Object* object) override {};
	bool OnRectCollided(Object* object, CollisionSide side) override { return false; };

};

