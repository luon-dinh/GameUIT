#pragma once
#include"Object.h"
#include"Collision.h"
class Item:public Object {
private:

public:
	int countFrame;
	int existTime;
	ItemType itemtype;
	void Update(float dt);
	BoundingBox getBoundingBox()override;

	Animation* animation;
	void Render();
	//Hàm dùng để xác định xem liệu object có được render trong grid không ?
	//Mặc định là sẽ được Render. Những object cần render theo kiểu đặc biệt thì ta override lại và để trống.
	virtual void RenderInGrid() { Render(); };
	int RenderWeight() { return RenderWeightOfObjects::ITEM_RENDER_WEIGHT; }
	void OnCollision(Object* object, collisionOut* colOut)override;
	bool OnRectCollided(Object* object, CollisionSide side)override;
	void OnNotCollision(Object* object)override {};
	Item(ItemType type);
	Item() {};
	~Item();
};