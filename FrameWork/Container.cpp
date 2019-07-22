#include "Container.h"
#include"Shield.h"


Container::Container()
{
	this->tag = Tag::CONTAINER;
	animation = new Animation(this->tag,0,2);
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
	auto shield = Shield::getInstance();
	if (Collision::getInstance()->IsCollide(this->getBoundingBox(), shield->getBoundingBox()))
	{
		animation->curframeindex = 1;
		if (numberItems >= 2)
		{
			items.at(numberItems-1)->isActive = true;
			numberItems--;
			items.at(numberItems - 1)->isActive = true;
			numberItems--;
		}
	}
	else
	{
		animation->curframeindex = 0;
	}
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

void Container::addItem(Item* item)
{
	items.push_back(item);
	numberItems++;
}
