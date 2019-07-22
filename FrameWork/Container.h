#pragma once
#include "Object.h"
#include"Item.h"
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
	Container();
	~Container();
};

