#pragma once
#include"Global.h"
#include"Sprite.h"
#include"Collision.h"
#include"Animation.h"

class Object {
protected:
	BOOL isActive;
public:
	Object() { vx = vy = 0; };
	virtual ~Object() {};

	D3DXVECTOR2 pos;
	float vx, vy;

	Tag tag;
	Type type;

	int width, height;

	virtual BoundingBox getBoundingBox();
	int getWidth();
	int getHeight();
	
	BoundingBox getStaticObjectBoundingBox();

	virtual void SetActive(bool value);
	virtual bool GetActive();

	virtual void Render();
	//Hàm dùng để xác định xem liệu object có được render trong grid không ?
	//Mặc định là sẽ được Render. Những object cần render theo kiểu đặc biệt thì ta override lại và để trống.
	virtual void RenderInGrid() { Render(); }; 

	//Do có một số item sẽ không bị xoá khỏi grid khi active zone của grid di chuyển.
	//Vì vậy cần phải override lại hàm này, xét tương ứng với từng object.
	//Mặc định là object sẽ bị delete khỏi Grid.
	virtual void DeactivateObject() { isActivated = true; }
	bool GetActivatedStatus() { return isActivated; }

	virtual void OnCollision(Object* object, collisionOut* colOut) {};
	virtual void OnCollisionWithDynamicObject(Object* object) {};
	virtual void Update(float dt);
	virtual void Respawn() {} ;
protected:
	//Mỗi khi Active Zone của Grid thay đổi thì sẽ gọi đến hàm DeactivateObject.
	//Hàm đó mặc định sẽ set biến isActivated = false, báo hiệu cho Grid biết là phải xoá nó.
	//Tuy nhiên ở các class như ItemLooter, sẽ override lại hàm này và không cho set biến isActivated.
	//Vì trạng thái của ItemLooter sẽ được lưu giữ lại chứ không mất đi như enemy. 
	bool isActivated = false; 
};
