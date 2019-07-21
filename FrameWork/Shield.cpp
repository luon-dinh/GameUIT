#include"Camera.h"
#include"Shield.h"



Shield * Shield::instance = NULL;

Shield::Shield()
{
	Player* player = Player::getInstance();
	if (!player)
		return;
	this->tag = Tag::SHIELD;
	this->vx = this->vy = 0;
	//sprites = SpriteManager::getInstance()->getSprites(this->tag, 0, 4);
	animation = new Animation(this->tag, 0, 4);
	Player::MoveDirection direction = Player::getInstance()->direction;
	this->pos.y = player->pos.y+10;
	animation->curframeindex = 2;
	//set vị trí ban đầu cua shield theo hướng di chuyển của player
	switch (direction)
	{
	case Player::MoveDirection::LeftToRight:
	{
		this->pos.x = player->pos.x - player->getWidth() / 2 - 2;
		this->pos.y = player->pos.y+10;
		break;
	}
	case Player::MoveDirection::RightToLeft:
	{
		this->pos.x = player->pos.x + player->getWidth() / 2 + 2;
		this->pos.y = player->pos.y+10;
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
	KeyboardManager* keyboard = KeyboardManager::getInstance();
	Player* player = Player::getInstance();
	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK) && player->hasShield && player->state != State::KICKING)
	{
		player->hasShield = false;
		switch (player->direction)
		{
		case Player::MoveDirection::LeftToRight:
		{
			this->vx = SHIELD_SPEED;
		//	this->direction = Player::MoveDirection::LeftToRight;
			break;
		}
		case Player::MoveDirection::RightToLeft:
		{
			this->vx = -SHIELD_SPEED;
			//this->direction = Player::MoveDirection::RightToLeft;
			break;
		}
		default:
			break;
		}
	}
}

void Shield::setFrameIndex(int index)
{
	this->animation->curframeindex = index;
}

void Shield::Update(float dt)
{
	Player* player = Player::getInstance();
	if (!player)
		return;
	Player::MoveDirection direction = Player::getInstance()->direction;// lấy hướng di chuyển của player player
	//kiểm tra nếu player đang giữ shield
	if (player->hasShield) {
		//nếu là shield up thì đổi sprite index
		if (player->state == State::SHIELD_UP)
		{
			this->animation->curframeindex = 2;
			return;
		}
		else if(player->state==State::SHIELD_DOWN)
		{
			this->animation->curframeindex = 3;
			return;
		}
		else
		{
			this->animation->curframeindex = 0;
		}
		//player đang ở trạng thái jump
		if (player->state == State::JUMPING)
		{
			this->animation->curframeindex = 1;
			this->pos.y = player->pos.y + 9;
			switch (direction)
			{
			case Player::MoveDirection::LeftToRight:
			{
				this->pos.x = player->pos.x - 3;//shield ở vị trí bên phải của player
				break;
			}
			case Player::MoveDirection::RightToLeft:
			{
				this->pos.x = player->pos.x + 3;//shield ở vị trí bên trái của player
				break;
			}
			default:
				break;
			}
			return;
		}
		//player đang ở trạng thái kick
		if (player->state == State::KICKING)
		{
			this->animation->curframeindex = 0;
			if (direction == Player::MoveDirection::LeftToRight)
			{
				this->pos.y = player->pos.y;
				this->pos.x = player->pos.x - 10;
			}
			else if (direction == Player::MoveDirection::RightToLeft)
			{
				this->pos.y = player->pos.y;
				this->pos.x = player->pos.x + 10;
			}
			return;
		}
		//player đang ở trạng thái stand
		if (player->state == State::STANDING)
		{
			this->pos.y = player->pos.y + 7;
			switch (direction)
			{
			case Player::LeftToRight:
			{
				this->pos.x = player->playerstate->getBoundingBox().right - 2;//shield ở vị trí bên phải của player
				break;
			}
			case Player::RightToLeft:
			{
				this->pos.x = player->playerstate->getBoundingBox().left + 2;//shield ở vị trí bên trái của player
				break;
			}
			default:
				break;
			}
			return;
		}
		//player đang ở trạng thái run
		if (player->state == State::RUNNING)
		{
			switch (direction)
			{
			case Player::MoveDirection::LeftToRight:
			{
				this->pos.x = player->playerstate->getBoundingBox().right - 1;//shield ở vị trí bên phải của player
				this->pos.y = player->pos.y + 10;
				break;
			}
			case Player::MoveDirection::RightToLeft:
			{
				this->pos.x = player->playerstate->getBoundingBox().left + 3;//shield ở vị trí bên trái của player
				this->pos.y = player->pos.y + 10;
				break;
			}
			default:
				break;
			}
			return;
		}
		//player đang ở trạng thái sit
		if (player->state == State::DUCKING)
		{
			switch (direction)
			{
			case Player::MoveDirection::LeftToRight:
			{
				this->pos.x = player->playerstate->getBoundingBox().right - 2;//shield ở vị trí bên phải của player
				this->pos.y = player->pos.y - 10;
				break;
			}
			case Player::MoveDirection::RightToLeft:
			{
				this->pos.x = player->playerstate->getBoundingBox().left + 1;//shield ở vị trí bên trái của player
				this->pos.y = player->pos.y - 10;
				break;
			}
			default:
				break;
			}
			return;
		}
	}
	//shield đã được player dùng để tấn công
	else
	{
		//xử lí update khi khiêng đang tấn công
		//update vị trí dự theo vị trí player
		if (this->state == ShieldState::Attack) {
			if (player->state == State::SHIELD_ATTACK)
				this->MoveAttack();
		}
	}
	this->InputHandler(dt);//hàm này hiện tại vô dụng
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
				D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));
				if (player->state != State::KICKING)
				{
					animation->Render(pos);
				}
				else
				{
					animation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
				}
				break;
			}
			case Player::MoveDirection::LeftToRight:
			{
				D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));
				if (player->state != State::KICKING) 
				{
					animation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
				}
				else
				{
					animation->Render(pos);
				}
				break;
			}
			default:
			{
				break; 
			}
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

void Shield::SetShieldState(Shield::ShieldState state) {
	this->state = state;
}

void Shield::MoveAttack() {
	auto player = Player::getInstance();

	// Khi bắt đầu di chuyển
	if (this->vx == 0 && this->round == 0) {
		if (player->direction == Player::MoveDirection::LeftToRight) {
		//	this->direction = Player::MoveDirection::LeftToRight;
			this->vx = SHIELD_INITIAL_SPEED;
			this->accelerator.x *= -1;
		}
		else {
			//this->direction = Player::MoveDirection::RightToLeft;
			this->vx = -SHIELD_INITIAL_SPEED;
		}
		// khiên khi bay đi chỉ bay ngang
		this->accelerator.y = 0;
		return;
	}

	// khi khiên bay tới giới hạn lần 1
	if (this->round == 0 && this->vx <= 0) {
		ReverseMoveDirection();
		this->round++;
	}
	else {
		// nếu khiên đã bay về tới player
		if (GetShieldToPlayer() == TRUE) {
			player->hasShield = TRUE;
		}
	}

	// cập nhật vận tốc và vị trí của khiên
	this->vx += this->accelerator.x;
	this->vy += this->accelerator.y;
	this->pos.x += this->vx;
	this->pos.y += this->vy;
}

void Shield::ReverseMoveDirection() {
	/*if (this->direction == Player::MoveDirection::LeftToRight) {
		this->direction = Player::MoveDirection::RightToLeft;
	}
	else {
		this->direction = Player::MoveDirection::LeftToRight;
	}*/

	float dentaY = this->pos.y - Player::getInstance()->pos.y;

	// khiên đang ở thấp hơn người
	if (dentaY < 0) {
		this->vy = SHIELD_INITIAL_SPEED;
	}
	else {
		// Khiên đang ở cao hơn người
		if (dentaY > 0)
			this->vy = -SHIELD_INITIAL_SPEED;
		else {
			this->vy = 0;
		}
	}

	// không xét gia tốc khi quay ngược về
	this->accelerator = D3DXVECTOR2(0, 0);
}


BOOL Shield::GetShieldToPlayer() {
	auto player = Player::getInstance();
	float dentaX = player->pos.x - this->pos.x;
	float dentaY = player->pos.y - this->pos.y;

	// khiên đã về tới player
	if (dentaX <= 2 && dentaY <= 2) {
		return TRUE;
	}

	return FALSE;

	// hướng vector vận tốc đã thay đổi
	if (this->vx * dentaX < 0) {
		this->vx *= -1;
	}
	if (this->vy * dentaY < 0) {
		this->vy *= -1;
	}
}