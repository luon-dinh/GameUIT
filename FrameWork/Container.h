#pragma once
#include "Object.h"
#include"ItemManager.h"
#include"Global.h"
class Container :
	public Object
{
public:
	Animation *animation;
	std::vector<Item*>items;
	int numberItems;

	BoundingBox getBoundingBox();
	void Update(float dt);
	void Render();
	//Container không bị xoá khỏi Grid. Vì vậy nó sẽ không bị deactivated.
	void DeactivateObjectInGrid() override {} ;
	void OnCollisionWithDynamicObject(Object* object);
	void OnCollision(Object * object, collisionOut* colOut) override;
	void Respawn() {};
	void addItem(Item* item);
	void SetPosition(D3DXVECTOR2 pos);
	//tạo mới một container cần phải tạo tất cả các item trước// dùng hàm loadallitem của itemmanager
	//truyền vào số lượng các items tương ứng của từng loại
	Container(int item1 = 1, int item2 = 1, int item3 = 1, int item4 = 1, int item5 = 1, int item6 = 1, int item7 = 1, int item8 = 1);
	~Container();
};

