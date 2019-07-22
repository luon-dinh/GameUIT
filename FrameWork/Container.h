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
	void OnCollision(Object* object, collisionOut *out);
	void Respawn() {};
	void addItem(Item* item);
	Container(int item1 = 1, int item2 = 1, int item3 = 1, int item4 = 1, int item5 = 1, int item6 = 1, int item7 = 1, int item8 = 1);
	~Container();
};

