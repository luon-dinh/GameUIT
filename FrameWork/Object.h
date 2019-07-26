#pragma once
#include"Global.h"
#include"Sprite.h"
#include"Collision.h"
#include"Animation.h"

class Object {

public:
	enum OnAir {
		Jumping,
		Falling,
		DropToWater,
		None,
		JumpFromWater
	};

	enum MoveDirection {
		LeftToRight,
		RightToLeft
	};


	enum MoveProperties {
		GoThrough,
		StoppedBySolidBox,
		Static
	};

	Object() { vx = vy = 0; };
	virtual ~Object() {};



	D3DXVECTOR2 pos;
	float vx, vy;
	D3DXVECTOR2 accelerator;

	Tag tag;
	Type type;

	int width, height;

	virtual BoundingBox getBoundingBox();
	int getWidth();
	int getHeight();
	
	BoundingBox getStaticObjectBoundingBox();

	virtual void SetActive(BOOL value);
	virtual BOOL GetActive();

	virtual void Render();
	//Hàm dùng để xác định xem liệu object có được render trong grid không ?
	//Mặc định là sẽ được Render. Những object cần render theo kiểu đặc biệt thì ta override lại và để trống.
	virtual void RenderInGrid() { Render(); }; 

	//Weight nhỏ render trước, weight lớn render sau.
	//Render sau sẽ che render trước.
	virtual int RenderWeight() { return RenderWeightOfObjects::OBJECT_RENDER_WEIGHT; }

	//Do có một số item sẽ không bị xoá khỏi grid khi active zone của grid di chuyển.
	//Vì vậy cần phải override lại hàm này, xét tương ứng với từng object.
	//Mặc định là object sẽ bị delete khỏi Grid.
	virtual void DeactivateObjectInGrid() { isActivatedInGrid = false; }
	bool GetActivatedInGridStatus() { return isActivatedInGrid; }

	//Hàm xác định xem object có khả năng được di chuyển trong Grid không. Mặc định là có.
	virtual bool IsMovableInGrid() { return true; }

	virtual std::list<Object*>* getAdditionalObjects() { return nullptr; };
	virtual void Update(float dt);
	virtual void Respawn() {} ;

	virtual void OnCollisionWithDynamicObject(Object* object) {}

	// Collision handler
	virtual void OnFallingOffGround();						// xử lý khi rơi khỏi ground
	virtual void OnStandingOnGround(Object* ground);		// xử lý khi đứng trên ground
	virtual void OnCollisionWithSolidBox(Object* solidBox, collisionOut* colOut);
	virtual void OnCollisionWithWater(Object* water, collisionOut* side);
	virtual void OnSmashSolidBox(Object* solid, CollisionSide side);
	virtual void OnHeadOnSolidBox(Object* solid);


	virtual MoveDirection GetMoveDirection();
	virtual void SetMoveDirection(MoveDirection direction);
	virtual void SetVy(float vy);
	virtual void SetVx(float vx);
	virtual void SetVelocity(D3DXVECTOR2 veloc);
	virtual void SetAccelerate(D3DXVECTOR2 acclerate);
	virtual void UpdatePosition();

	virtual OnAir GetOnAirState();
	virtual OnAir GetPreOnAirState();
	virtual void SetOnAirState(OnAir airState);

	virtual bool IsOnGround();
	virtual Object* GetStandingGround();
	virtual void SetStandingGround(Object* ground);

	virtual void SetMoveProperty(MoveProperties moveProp);
	virtual bool IsStopBySolidBox();
	virtual bool IsStopLeft();
	virtual bool IsStopRight();

	// Override hàm này để có thể thay đổi state
	virtual void ChangeState(State stateName)							= 0;

	// Handler chung của các trường hợp collision
	virtual void OnCollision(Object* object, collisionOut* colOut)		= 0;
	virtual void OnNotCollision(Object* object)							= 0;
	virtual bool OnRectCollided(Object* object, CollisionSide side)		= 0;

protected:
	BOOL isActive;
	//Mỗi khi Active Zone của Grid thay đổi thì sẽ gọi đến hàm DeactivateObject.
	//Hàm đó mặc định sẽ set biến isActivated = false, báo hiệu cho Grid biết là phải xoá nó.
	//Tuy nhiên ở các class như ItemLooter, sẽ override lại hàm này và không cho set biến isActivated.
	//Vì trạng thái của ItemLooter sẽ được lưu giữ lại chứ không mất đi như enemy. 
	bool isActivatedInGrid = true;



	MoveDirection direction;

	OnAir onAirState;
	OnAir preOnAirState;

	Object* currentGround;
	Object* collidedSolidBox;

	MoveProperties moveProperty;

	bool smashLeft;
	bool smashRight;
};
