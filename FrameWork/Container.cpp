#include "Container.h"
#include"Shield.h"
#include"Player.h"
#include"Camera.h"
#include "Debug.h"
#include "SceneManager.h"
#include<cstdlib>

Container::Container(ItemType type)
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
	auto player = Player::getInstance();
	if (Collision::getInstance()->IsCollide(this->getBoundingBox(), player->getBoundingBox()))
	{
		if (player->state == State::STAND_PUNCH || player->state == State::DUCKING_PUNCHING || player->state == State::KICKING)
		{
			auto scene = SceneManager::getInstance();
			ticuframe = 500;
			if (item != nullptr)
			{
				item->pos = this->pos;
				//Nếu thêm item thành công thì mới xoá item ra khỏi sự quản lý của Container.
				//Do có thể có trường hợp map đang chứa nhiều hơn 3 item sẽ không Add thêm được.
				if (scene->AddObjectToCurrentScene(item))
				{
					//Nếu không phải cục exit hoặc player có thể qua tiếp màn sau rồi thì không xuất cục đó nữa.
					if (!(item->itemtype == ItemType::EXIT) || player->CanGoNextScene())
					{
						item = nullptr;
					}
					//Nếu vẫn cần nó xuất hiện lần 2 thì ta phải thêm một cục mới.
					else
						item = new Item(item->itemtype);
				}
				return;
			}
			if (numberItems != 0)
			{
				Item* newItem = new Item(ItemType::STAR);
				newItem->pos = this->pos;
				//Nếu thêm item thành công thì mới xoá item ra khỏi sự quản lý của Container.
				//Do có thể có trường hợp map đang chứa nhiều hơn 3 item sẽ không Add thêm được.
				if (scene->AddObjectToCurrentScene(newItem))
					numberItems--;
			}
		}
	}
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



void Container::OnCollision(Object* object, collisionOut* colOut)
{
	Player* player = Player::getInstance();
	Shield* shield = Shield::getInstance();
	SceneManager* scene = SceneManager::getInstance();
	switch (object->tag)
	{
	case Tag::SHIELD:
	{
		if (shield->state == Shield::ShieldState::Attack)
		{
			animation->curframeindex = 1;
			ticuframe = 500;
			if (item != nullptr)
			{
				item->pos = this->pos;
				//Nếu thêm item thành công thì mới xoá item ra khỏi sự quản lý của Container.
				//Do có thể có trường hợp map đang chứa nhiều hơn 3 item sẽ không Add thêm được.
				if (scene->AddObjectToCurrentScene(item))
				{
					//Nếu không phải cục exit hoặc player có thể qua tiếp màn sau rồi thì không xuất cục đó nữa.
					if (!(item->itemtype == ItemType::EXIT) || player->CanGoNextScene())
					{
						item = nullptr;
					}
					//Nếu vẫn cần nó xuất hiện lần 2 thì ta phải thêm một cục mới.
					else
						item = new Item(item->itemtype);
				}
				return;
			}
			if (numberItems != 0)
			{
				Item* newItem = new Item(ItemType::STAR);
				newItem->pos = this->pos;
				//Nếu thêm item thành công thì mới xoá item ra khỏi sự quản lý của Container.
				//Do có thể có trường hợp map đang chứa nhiều hơn 3 item sẽ không Add thêm được.
				if (scene->AddObjectToCurrentScene(newItem))
					numberItems--;
			}
		}
		break;
	}
	default:
		break;
	}
}

bool Container::OnRectCollided(Object* object, CollisionSide side)
{
	return true;
}


void Container::OnNotCollision(Object* object)
{
	
}

void Container::SetPosition(D3DXVECTOR2 pos)
{
	
}