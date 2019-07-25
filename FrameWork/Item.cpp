#include"Item.h"
#include"Camera.h"

Item::Item(Type type)
{
	this->tag = ITEM;
	this->type = type;
	this->vy = ITEM_SPEED;
	this->vx = 0;
	existTime = ITEM_EXIST_TIME;
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

}

void Item::Update(float dt)
{
	this->pos.y += this->vy;
	existTime -= dt;
	if (existTime <= 0)
	{
		DeactivateObjectInGrid();
	}
	animation->Update(dt);
}
void Item::Render()
{
	if (existTime > 0.75*ITEM_EXIST_TIME)
	{

	}
	D3DXVECTOR3 position = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	animation->Render(position);
}

BoundingBox Item::getBoundingBox()
{
	BoundingBox box;
	box.top = this->pos.y + 8;
	box.bottom = this->pos.y - 8;
	box.left = this->pos.x - 6;
	box.right = this->pos.x + 6;
	box.vx = this->vx;
	box.vy = this->vy;
	return box;
}

void Item::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
	case Type::WATERRL:
		this->vx = this->vy = 0;
		this->pos.y = object->pos.y + this->getHeight() / 2;
		break;
		//xuwr lis va chamj voiws player
	case Type::NONE:
		DeactivateObjectInGrid();
		break;
	default:
		break;
	}
}