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
	void addItem(Item* item);
	Container(int item1 = 0, int item2=0, int item3=0, int item4=0, int item5=0, int item6=0, int item7=0, int item8=0);
	~Container();
};

