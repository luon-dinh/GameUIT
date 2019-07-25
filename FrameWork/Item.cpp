#include"Item.h"
#include"Camera.h"
Item::Item(ItemType itemtype)
{
	this->tag = ITEM;
	this-> itemtype= itemtype;
	this->vx = 0;
	this->vy = -ITEM_SPEED;
	this->existTime = ITEM_EXIST_TIME;
	this->countFrame = 0;
	switch (itemtype)
	{
	case ItemType::UP:
		animation = new Animation(Tag::ITEM, 0);
		break;
	
	case ItemType::STAR:
		animation = new Animation(Tag::ITEM, 1);
		break;
	case ItemType::EXIT:
		animation = new Animation(Tag::ITEM, 2, 4);
		break;
	case ItemType::HEART:
		animation = new Animation(Tag::ITEM, 4);
		break;
	case ItemType::HALFHEART:
		animation = new Animation(Tag::ITEM, 5);
		break;
	case ItemType::HP:
		animation = new Animation(Tag::ITEM, 6);
		break;
	case ItemType::GEM:
		animation = new Animation(Tag::ITEM, 7,9);
		break;
	case ItemType::SMALLGEM:
		animation = new Animation(Tag::ITEM, 9,11);
		break;
	}
}
Item::~Item()
{

}

void Item::Update(float dt)
{
	countFrame++;

	if (countFrame<15)
		this->vy = ITEM_SPEED;
	else
	{
		if(this->vy!=0)
			this->vy = -ITEM_SPEED;
	}

	this->pos.y += this->vy;
	animation->Update(dt);
	if(this->vy==0)
		existTime -= dt;
	if (existTime <= 0)
	{
		DeactivateObjectInGrid();
	}
}
void Item::Render()
{
	D3DXVECTOR3 position = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	if (existTime < 0.25*ITEM_EXIST_TIME)
	{
		if((int)existTime%2==0)
			animation->Render(position);
		return;
	}
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
		if(object->tag==Tag::PLAYER)
			DeactivateObjectInGrid();
		break;
	default:
		break;
	}
}