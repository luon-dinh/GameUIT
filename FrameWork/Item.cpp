#include"Item.h"

Item::Item(int frameIndex, D3DXVECTOR2 pos)
{
	this->pos = pos;
	sprite = animation->getSprite(frameIndex);
}
Item::~Item()
{
	if (sprite)
		delete sprite;
}

void Item::Update(float dt)
{
	if (isActive)
	{
		this->pos.y -= 2;
	}
}
void Item::Render()
{
	if (isActive)
	{
		sprite->Render(this->pos);
	}
}

BoundingBox Item::getBoundingBox()
{
	BoundingBox box;
	box.top = this->pos.y + 7;
	box.bottom = this->pos.y - 7;
	box.left = this->pos.x - 6;
	box.right = this->pos.x + 6;
}

void Item::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->type)
	{
		//va chạm với player
		case Type::NONE:
		{
			isActive = FALSE;
		}
		//va chạm với đất
		case Type::GROUND:
		{
			this->pos.y = object->pos.y + this->getHeight() / 2;
			break;
		}
	}
}