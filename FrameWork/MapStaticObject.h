#pragma once
#include "Object.h"

class MapStaticObject : public Object
{
public:
	MapStaticObject()
	{
		tag = Tag::STATICOBJECT;
	}
	BoundingBox getBoundingBox () override
	{
		BoundingBox box;
		box.top = this->pos.y + this->height / 2;
		box.left = this->pos.x - this->width / 2;
		box.bottom = box.top - this->height;
		box.right = box.left + this->width;
		box.vx = box.vy = 0;
		return box;
	}
	//Override lại hàm này, không cho phép xoá ra khỏi Grid khi camera di chuyển.
	void DeactivateObjectInGrid() override {};
	bool IsMovableInGrid() override { return false; }
};