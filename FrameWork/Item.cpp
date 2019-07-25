#include"Item.h"
#include"Camera.h"

Item::Item(Type type)
{
	this->tag = ITEM;
	this->type = type;
	this->vy = ITEM_SPEED;
	existTime = ITEM_EXIST_TIME;
	this->isActive = false;
	switch (type)
	{
	case Type::UP:
		animation = new Animation(Tag::ITEM, 0);
		break;
	
	case Type::STAR:
		animation = new Animation(Tag::ITEM, 1);
		break;
	case Type::EXIT:
		animation = new Animation(Tag::ITEM, 2, 4);
		break;
	case Type::HEART:
		animation = new Animation(Tag::ITEM, 4);
		break;
	case Type::HALFHEART:
		animation = new Animation(Tag::ITEM, 5);
		break;
	case Type::HP:
		animation = new Animation(Tag::ITEM, 6);
		break;
	case Type::GEM:
		animation = new Animation(Tag::ITEM, 7,9);
		break;
	case Type::SMALLGEM:
		animation = new Animation(Tag::ITEM, 9,11);
		break;
	
	}
}
Item::~Item()
{
	if (animation)
		delete animation;
}

void Item::Update(float dt)
{
	if (isActive)
	{
		this->pos.y += this->vy;
		existTime -= dt;
		if (existTime <= 0)
		{
			isActive = false;
			DeactivateObjectInGrid();
		}
		animation->Update(dt);
	}
}
void Item::Render()
{
	if (isActive)
	{
		D3DXVECTOR3 position = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		animation->Render(position);
	}
}

BoundingBox Item::getBoundingBox()
{
	BoundingBox box;
	box.top = this->pos.y + 7;
	box.bottom = this->pos.y - 7;
	box.left = this->pos.x - 6;
	box.right = this->pos.x + 6;
	box.vx = box.vy = 0;
	return box;
}

void Item::OnCollision(Object* object, collisionOut* colOut)
{
	if (!isActive)
		return;
	switch (object->type)
	{
		//va chạm với player
		case Type::NONE:
		{
			this->isActive = false;
			
			switch (this->type)
			{
			case Type::HEART:
				break;
			case Type::HALFHEART:
				break;
			case Type::HP:
				break;
			case Type::UP:
				break;
			case Type::GEM:
				break;
			case Type::SMALLGEM:
				break;
			case Type::EXIT:
				break;
			default:
				break;
			}
			DeactivateObjectInGrid();
		}
		//va chạm với đất
		case Tag::STATICOBJECT:
		{
			this->vy = this->vx = 0;
			this->pos.y = object->pos.y+this->getHeight()/2;
		}
	}
}