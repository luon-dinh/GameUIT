#include "Container.h"
#include"Shield.h"
#include"Camera.h"
#include "Debug.h"
#include<cstdlib>

Container::Container(Type type )
{
	ItemManager* itemManager = ItemManager::getInstance();
	this->tag = Tag::ITEMCONTAINER;
	this->type = Type::ITEMCONTAINERTYPE;
	this->vx = this->vy = 0;
	numberItems = 0;
	animation = new Animation(this->tag,0,2);
	int numberStars = rand() % 7 ;
	for (int i = 0; i < numberStars; i++)
	{
		addItem(new Item(Type::STAR));
	}
	switch (type)
	{
	case HEART:
		addItem(new Item(Type::HEART));
		break;
	case HALFHEART:
		addItem(new Item(Type::HALFHEART));
		break;
	case EXIT:
		addItem(new Item(Type::EXIT));
		break;
	case GEM:
		addItem(new Item(Type::GEM));
		break;
	case SMALLGEM:
		addItem(new Item(Type::SMALLGEM));
		break;
	case HP:
		addItem(new Item(Type::HP));
		break;
	case UP:
		addItem(new Item(Type::UP));
		break;
	default:
		break;
	}
}


Container::~Container()
{
	
}

void Container::Update(float dt)
{
	
	ticuframe -= dt;
	if (ticuframe <= 0)
	{
		animation->curframeindex = 0;
		ticuframe = 0;
	}

	for (auto item : items)
		item->Update(dt);
}

void Container::Render()
{
	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x,this->pos.y,0));
	//animation->Render(this->pos);
	animation->getSprite(animation->curframeindex)->Render(pos);
	for (auto item : items)
		item->Render();
}

BoundingBox Container::getBoundingBox()
{
	BoundingBox box;
	box.top = this->pos.y + 8;
	box.bottom = this->pos.y - 8;
	box.left = this->pos.x - 6;
	box.right = this->pos.x + 6;
	box.vx = box.vy = 0;
	return box;
}

void Container::addItem(Item *item)
{
	items.push_back(item);
	numberItems++;
}



void Container::OnCollision(Object* object, collisionOut* colOut)
{
	Player* player = Player::getInstance();
	Shield* shield = Shield::getInstance();
	// nếu container va chạm với shield hoặc bị player đánh
	if ((object->tag == Tag::SHIELD&&shield->state==Shield::ShieldState::Attack) || ((player->state == State::STAND_PUNCH || player->state == DUCKING_PUNCHING) && object->tag == Tag::PLAYER))
	{
		animation->curframeindex = 1;
		ticuframe = 500;
		if (numberItems != 0)
		{
			items[numberItems - 1]->pos = this->pos;
			items[numberItems - 1]->existTime = ITEM_EXIST_TIME;
			items[numberItems - 1]->vy = ITEM_SPEED;
			additionalItems.push_back(items[numberItems - 1]);
			if (items[numberItems - 1]->type != Type::EXIT)
			{
				numberItems--;
			}
		}
	}
	PrintDebug("\nCollide with Container !!");
}
void Container::SetPosition(D3DXVECTOR2 pos)
{
	this->pos = pos;
	for (auto item : items)
		item->pos = this->pos;
}