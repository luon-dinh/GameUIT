#include "Container.h"
#include"Shield.h"


Container::Container(int item1 , int item2 , int item3 , int item4 , int item5 , int item6 , int item7 , int item8 )
{
	ItemManager* itemManager = ItemManager::getInstance();
	this->tag = Tag::ITEMCONTAINER;
	this->type = Type::ITEMCONTAINERTYPE;
	animation = new Animation(this->tag,0,2);
	for (int i = 0; i < item1; i++)
	{
		addItem(itemManager->getItem(0));
	}
	for (int i = 0; i < item2; i++)
	{
		addItem(itemManager->getItem(1));
	}
	for (int i = 0; i < item3; i++)
	{
		addItem(itemManager->getItem(2));
	}
	for (int i = 0; i < item4; i++)
	{
		addItem(itemManager->getItem(3));
	}
	for (int i = 0; i < item5; i++)
	{
		addItem(itemManager->getItem(4));
	}
	for (int i = 0; i < item6; i++)
	{
		addItem(itemManager->getItem(5));
	}
	for (int i = 0; i < item7; i++)
	{
		addItem(itemManager->getItem(6));
	}
	for (int i = 0; i < item8; i++)
	{
		addItem(itemManager->getItem(7));
	}
}


Container::~Container()
{
	if (animation)
		delete animation;
	for (auto it : items)
		it = nullptr;
	items.clear();
}

void Container::Update(float dt)
{
	this->animation->curframeindex = 0;
}

void Container::Render()
{
	animation->Render(this->pos);
}

BoundingBox Container::getBoundingBox()
{
	BoundingBox box;
	box.top = this->pos.y + 8;
	box.bottom = this->pos.y - 8;
	box.left = this->pos.x - 8;
	box.right = this->pos.x + 8;
	return box;
}

void Container::addItem(Item *item)
{
	items.push_back(item);
	numberItems++;
}

void Container::OnCollision(Object* object, collisionOut *colOut)
{
	Player* player = Player::getInstance();
	if(object->tag==Tag::SHIELD||player->state==State::STAND_PUNCH||player->state==DUCKING_PUNCHING)
	{
		animation->curframeindex = 1;
		animation->DelayCurrentFrame(50);
		if (numberItems != 0)
		{
			items.at(numberItems - 1)->isActive = true;
			numberItems--;
		}
	}
}