#include "Container.h"
#include"Shield.h"
#include"Camera.h"
#include "Debug.h"
#include<cstdlib>

Container::Container(ItemType type )
{
	ItemManager* itemManager = ItemManager::getInstance();
	this->tag = Tag::ITEMCONTAINER;
	this->type = Type::ITEMCONTAINERTYPE;
	this->vx = this->vy = 0;
	numberItems = 0;
	animation = new Animation(this->tag,0,2);
	numberItems = 15;
	item = new Item(type);
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
}

void Container::Render()
{
	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x,this->pos.y,0));
	//animation->Render(this->pos);
	animation->getSprite(animation->curframeindex)->Render(pos);
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



void Container::OnCollision(Object* object, collisionOut* colOut)
{
	Player* player = Player::getInstance();
	Shield* shield = Shield::getInstance();
	// nếu container va chạm với shield hoặc bị player đánh
	if ((object->tag == Tag::SHIELD&&shield->state==Shield::ShieldState::Attack) || ((player->state == State::STAND_PUNCH || player->state == DUCKING_PUNCHING) && object->tag == Tag::PLAYER))
	{
		animation->curframeindex = 1;
		ticuframe = 500;
		if (item != nullptr)
		{
			item->pos = this->pos;
			additionalItems.push_back(item);
			item = nullptr;
			return;
		}
		if (numberItems != 0)
		{
			Item* newItem = new Item(ItemType::STAR);
			newItem->pos = this->pos;
			additionalItems.push_back(newItem);
			numberItems--;
		}
	}
	PrintDebug("\nCollide with Container !!");
}
void Container::SetPosition(D3DXVECTOR2 pos)
{
	
}