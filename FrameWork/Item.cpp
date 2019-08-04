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
	isCollidable = false;
}
Item::~Item()
{

}

void Item::Update(float dt)
{
	countFrame++;

	if (countFrame < 20)
	{
		this->vy = ITEM_SPEED;
		isCollidable = false;
	}
	else
	{
		if (this->vy != 0)
		{
			this->vy = -ITEM_SPEED;
			isCollidable = true;
		}
			
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
	box.vx = this->vx;
	box.vy = this->vy;
	auto sprite = this->animation->getSprite(this->animation->curframeindex);
	RECT rect = sprite->getRECT();
	height = rect.top - rect.bottom;
	width = rect.right - rect.left;
	box.top = this->pos.y + height / 2;
	box.bottom = this->pos.y - height / 2;
	box.left = this->pos.x - width / 2;
	box.right = this->pos.x + width / 2;
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
		this->pos.y = object->getBoundingBox().top + this->getHeight() / 2 - 4;
		break;
		//xuwr lis va chamj voiws player
	default:
		break;
	}
	//if (object->tag == Tag::PLAYER)
	//	DeactivateObjectInGrid();
}

float Item::getHeight()
{
	auto sprite = this->animation->getSprite(this->animation->curframeindex);
	RECT rect = sprite->getRECT();
	height = rect.top - rect.bottom;
	return height;
}

float Item::getWidth()
{
	auto sprite = this->animation->getSprite(this->animation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	return width;
}

bool Item::OnRectCollided(Object* object, CollisionSide side)
{
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
	case Type::WATERRL:
		this->vx = this->vy = 0;
		this->pos.y = object->getBoundingBox().top + this->getHeight() / 2 - 4;
		break;
		//xuwr lis va chamj voiws player
	default:
		break;
	}
	if (object->tag == Tag::PLAYER)
		DeactivateObjectInGrid();
	return true;
}