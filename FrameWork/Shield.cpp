#include "Shield.h"
#include"Camera.h"

typedef Shield::State S_State;

Shield * Shield::instance = NULL;

Shield::Shield()
{
	Player* player = Player::getInstance();
	if (!player)
		return;
	this->tag = Tag::SHIELD;
	this->vx = this->vy = 0;
	this->accelerator = D3DXVECTOR2(SHIELD_MOVE_ACCELERATOR, SHIELD_MOVE_ACCELERATOR);
	this->round = 0;

	//sprites = SpriteManager::getInstance()->getSprites(this->tag, 0, 4);
	animation = new Animation(this->tag, 0, 4);

	LoadAllStates();
	ChangeState(Shield::State::ShieldNormal);
}


void Shield::LoadAllStates() {
	this->shieldStates[S_State::ShieldAttack] = new ShieldAttackState();
	this->shieldStates[S_State::ShieldDown] = new ShieldDownState();
	this->shieldStates[S_State::ShieldUp] = new ShieldUpState();
	this->shieldStates[S_State::ShieldJump] = new ShieldJumpState();
	this->shieldStates[S_State::ShieldNormal] = new ShieldNormalState();
	this->shieldStates[S_State::None] = NULL;
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

void Shield::ChangeState(Shield::State state) {
	this->state = this->shieldStates[state];

	switch (state) {
		case S_State::ShieldRun:
		case S_State::ShieldNormal:		animation->curframeindex = 0;break;
		case S_State::ShieldJump:		animation->curframeindex = 1;break;
		case S_State::ShieldAttack:
		case S_State::ShieldUp:			animation->curframeindex = 2;break;
		case S_State::ShieldDown:		animation->curframeindex = 3;break;
	}
}

//xư lí sự kiện nhấn phím cho shield
//void Shield::InputHandler(float dt)
//{
//	KeyboardManager* keyboard = KeyboardManager::getInstance();
//	Player* player = Player::getInstance();
//	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK) && player->hasShield&&player->state != State::KICKING)
//	{
//		player->hasShield = false;
//		switch (player->direction)
//		{
//		case Player::ShieldDirection::LeftToRight:
//		{
//			this->vx = SHIELD_SPEED;
//			break;
//		}
//		case Player::ShieldDirection::RightToLeft:
//		{
//			this->vx = -SHIELD_SPEED;
//			break;
//		}
//		default:
//			break;
//		}
//	}
//}

void Shield::setFrameIndex(int index)
{
	this->animation->curframeindex = index;
}

void Shield::Update(float dt)
{	
	if (this->state == NULL)
		return;

	this->state->Update(dt);
}

void Shield::Render()
{
	Player* player = Player::getInstance();
	if (!player)
		return;
	
	if (!this->state)
		return;

	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));

	if (this->direction == ShieldDirection::LeftToRight) {
		this->animation->Render(this->pos, TransformationMode::FlipHorizontal);
	}
	else {
		this->animation->Render(this->pos);
	}
}

void Shield::MoveAttack() {
	auto player = Player::getInstance();

	// Khi bắt đầu di chuyển
	if (this->vx == 0 && this->round == 0) {
		if (player->direction == Player::MoveDirection::LeftToRight) {
			this->direction = ShieldDirection::LeftToRight;
			this->vx = SHIELD_INITIAL_SPEED;
			this->accelerator.x *= -1;
		}
		else {
			this->direction = ShieldDirection::RightToLeft;
			this->vx = -SHIELD_INITIAL_SPEED;
		}
		// khiên khi bay đi chỉ bay ngang
		this->accelerator.y = 0;
		return;
	}

	// khi khiên bay tới giới hạn lần 1
	if (this->round == 0 && this->vx <= 0) {
		ReverseShieldDirection();
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

void Shield::ReverseShieldDirection() {
	if (this->direction == ShieldDirection::LeftToRight) {
		this->direction = ShieldDirection::RightToLeft;
	}
	else {
		this->direction = ShieldDirection::LeftToRight;
	}

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

void Shield::OnCollision(Object* object, collisionOut out)
{
	//xu li va cham
}