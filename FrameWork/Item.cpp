#include"Item.h"
#include"Camera.h"

Item::Item(Type type)
{
	Animation* animation = new Animation(Tag::ITEM, 0, 8);
	this->tag = ITEM;
	this->type = type;
	this->vy = 0;
	isActive = true;
	switch (type)
	{
	case Type::ITEM1:
		sprite = animation->getSprite(0);
		break;
	case Type::ITEM2:
		sprite = animation->getSprite(1);
		break;
	case Type::ITEM3:
		sprite = animation->getSprite(2);
		break;
	case Type::ITEM4:
		sprite = animation->getSprite(3);
		break;
	case Type::ITEM5:
		sprite = animation->getSprite(4);
		break;
	case Type::ITEM6:
		sprite = animation->getSprite(5);
		break;
	case Type::ITEM7:
		sprite = animation->getSprite(6);
		break;
	case Type::ITEM8:
		sprite = animation->getSprite(7);
		break;
	}
	delete animation;
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
		this->pos.y += this->vy;
	}
}
void Item::Render()
{
	if (isActive)
	{
		D3DXVECTOR3 position = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		sprite->Render(position);
	}
}

BoundingBox Item::getBoundingBox()
{
	BoundingBox box;
	box.top = this->pos.y + 7;
	box.bottom = this->pos.y - 7;
	box.left = this->pos.x - 6;
	box.right = this->pos.x + 6;
	return box;
}

void Item::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->type)
	{
		//va chạm với player
		case Type::NONE:
		{
			this->isActive = false;
		}
		//va chạm với đất
		case Type::GROUND:
		{
			this->pos.y = object->pos.y + this->getHeight() / 2;
			this->vy = 0;
			break;
		}
	}
}