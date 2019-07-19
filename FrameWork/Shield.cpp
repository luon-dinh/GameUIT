#include "Shield.h"

Shield * Shield::instance = NULL;

Shield::Shield()
{
	Player* player = Player::getInstance();
	if (!player)
		return;
	sprites = SpriteManager::getInstance()->getSprites(this->tag, 0, 4);
	Player::MoveDirection direction = Player::getInstance()->direction;
	this->pos.y = player->pos.y;
	this->currentSpriteIndex = 0;
	//set vị trí ban đầu cua shield theo hướng di chuyển của player
	switch (direction)
	{
	case Player::LeftToRight:
	{
		this->pos.x = player->playerstate->getBoundingBox().right;
		break;
	}
	case Player::RightToLeft:
	{
		this->pos.x = player->playerstate->getBoundingBox().right;
		break;
	}
	default:
		break;
	}
}

Shield* Shield::getInstance()
{
	if (!instance)
		instance = new Shield();
	return instance;
}

Shield::~Shield()
{
}
//xư lí sự kiện nhấn phím cho shield
void Shield::InputHandler(float dt)
{
	KeyboardManager *keyBoard = KeyboardManager::getInstance();
	Player* player = Player::getInstance();
	if (!player)
		return;
	//nếu shield đang được player giữ
	if (player->hasShield)
	{
		keyBoard->getState(dt);

		if (keyBoard->isKeyDown(PLAYER_SHIELD_UP))
		{
			this->pos.y = player->getBoundingBox().top;
			this->pos.x = player->pos.x;
		}
		//còn thiếu sự kiện rớt xuống shield xuống
	}
}

void Shield::Update(float dt)
{
	this->InputHandler(dt);
	Player* player = Player::getInstance();
	if (!player)
		return;
	//kiểm tra nếu player đang giữ shield
	if (player->hasShield) {
		Player::MoveDirection direction = Player::getInstance()->direction;// lấy hướng di chuyển của player player
		//set vị trí của shied theo hướng di chuyển của player
		switch (direction)
		{
		case Player::LeftToRight:
		{
			this->pos.x = player->playerstate->getBoundingBox().right;//shield ở vị trí bên phải của player
			break;
		}
		case Player::RightToLeft:
		{
			this->pos.x = player->playerstate->getBoundingBox().right;//shield ở vị trí bên trái của player
			break;
		}
		default:
			break;
		}
	}
	//shield đã đc player dùng để tấn công
	else
	{
		//xử lí update khi khiêng đang tấn công
		//update vị trí dự theo vị trí player
	}
}

void Shield::Render()
{
	Player* player = Player::getInstance();
	if (!player)
		return;
	//shield is on player
	if (player->hasShield)
	{
		switch (player->direction)
		{
		case Player::MoveDirection::RightToLeft:
		{
			sprites[currentSpriteIndex]->Render(TransformationMode::FlipHorizontal, 0, D3DXVECTOR2(this->pos));//flip shield do sprite ngược chiều hướng di chuyển
		}
		case Player::MoveDirection::LeftToRight:
		{
			sprites[currentSpriteIndex]->Render(D3DXVECTOR2(this->pos));//vẽ sprite bình thường
		}
		default:
			break;
		}
	}
	//shield đang được dùng để tấn công
	else
	{
		//vẽ theo trạng thái tấn công
	}
}

void Shield::OnCollision(Object* object, collisionOut out)
{
	//xu li va cham
}