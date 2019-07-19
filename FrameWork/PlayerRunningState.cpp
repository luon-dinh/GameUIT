#include "PlayerRunningState.h"



PlayerRunningState::PlayerRunningState()
{
	state = RUNNING;
	this->timeFlip = 0;
	this->befDash = BeforeDash::None;
}


PlayerRunningState::~PlayerRunningState()
{
}

void PlayerRunningState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	if (player == NULL || keyboard == NULL)
		return;

	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		if (this->befDash == BeforeDash::DashLeft) {
			// đã có thể dash
			if (this->timeFlip > 0 && this->timeFlip <= MAX_FLIP_TIME) {
				player->ChangeState(State::DASHING);
				this->befDash = BeforeDash::None;
				this->timeFlip = 0;
				return;
			}
			// nhấn phím quá chậm
			else {
				this->timeFlip = 0;
			}
		}
		else {
			if (this->befDash == BeforeDash::None) {
				this->befDash == BeforeDash::DashLeft;
			}
			else {
				this->befDash = BeforeDash::None;
			}
		}
		// dash hướng phải hoặc chưa dash
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
		}
		return;
	}

	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
		}
		return;
	}

	// Không phím nào được nhấn thì chuyển sang trạng thái đứng yên
	player->ChangeState(State::STANDING);
}

void PlayerRunningState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;
	auto player = Player::getInstance();

	// collide with ground
	if (object->type == Type::GROUND) {
	}
}

BOOL PlayerRunningState::ChangeToDash(BeforeDash currentDash) {
	if (currentDash == BeforeDash::None) {
		this->befDash = currentDash;
		return FALSE;
	}
	if (this->befDash == currentDash) {
		// đã có thể dash
		if (this->timeFlip > 0 && this->timeFlip <= MAX_FLIP_TIME) {
			this->befDash = BeforeDash::None;
			this->timeFlip = 0; 
			return TRUE;
		}
		// nhấn phím quá chậm
		else {
			this->timeFlip = 0;
		}
	}
	else {
		if (this->befDash == BeforeDash::None) {
			this->befDash == BeforeDash::DashLeft;
		}
		else {
			this->befDash = BeforeDash::None;
		}
	}
}

void PlayerRunningState::Update(float dt)
{
	this->InputHandler();
}


BoundingBox PlayerRunningState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 21;
	box.bottom = player->pos.y - 21;
	box.left = player->pos.x - 13;
	box.right = player->pos.x + 12;
	return box;
}