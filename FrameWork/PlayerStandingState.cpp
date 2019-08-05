#include"PlayerStandingState.h"
#include "Debug.h"

PlayerStandingState::PlayerStandingState()
{
	state = STANDING;
	this->frameFlip = 0;
	this->flipStart = FALSE;
	this->befDash = BeforeDash::None;
}

void PlayerStandingState::Update(float dt)
{
	this->InputHandler();
}

void PlayerStandingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();

	if (player == NULL || keyboard == NULL)
		return;

	// Nếu flip đang bật thì bắt đầu tăng frame
	if (player->GetPreviousState()->state != State::RUNNING)
		StopFrameFlip();

	if (flipStart) {
		this->frameFlip++;
	}

	int timePressedMove = 0;

	// di chuyển qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT) && !player->IsStopLeft())
	{
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		bool keyPressed = keyboard->getKeyPressedOnce(PLAYER_MOVE_LEFT, timePressedMove);
		if (keyPressed || (!keyPressed && timePressedMove <= 20)) {
			if (ChangeToDash(BeforeDash::DashLeft)) {
				player->ChangeState(State::DASHING);
				StopFrameFlip();
				return;
			}
		}
		else
		{
			if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
				return;
		}
		player->ChangeState(State::RUNNING);
		return;
	}
	// di chuyển qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT) && !player->IsStopRight())
	{
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		bool keyPressed = keyboard->getKeyPressedOnce(PLAYER_MOVE_RIGHT, timePressedMove);
		if (keyPressed || (!keyPressed && timePressedMove <= 20)) {
			if (ChangeToDash(BeforeDash::DashRight)) {
				player->ChangeState(State::DASHING);
				StopFrameFlip();
				return;
			}
		}
		else
		{
			if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
				return;
		}
		player->ChangeState(State::RUNNING);
		return;
	}
	// nhảy lên
	if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		StopFrameFlip();
		return;	
	}
	// ngồi xuống
	if (keyboard->isKeyDown(PLAYER_SIT)) {
		player->ChangeState(State::DUCKING);
		StopFrameFlip();
		return;
	}
	// giơ khiên lên
	if (keyboard->isKeyDown(PLAYER_SHIELD_UP)) {
		player->ChangeState(State::SHIELD_UP);
		StopFrameFlip();
		return;
	}

	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		if (player->hasShield)
			player->ChangeState(State::SHIELD_ATTACK);
		else {
			player->ChangeState(State::STAND_PUNCH);
		}
	}
}

BOOL PlayerStandingState::ChangeToDash(BeforeDash currentDash) {
	if (currentDash == BeforeDash::None) {
		StopFrameFlip();
		return FALSE;
	}
	// restart the frame flip
	if (this->befDash != currentDash) {
		this->befDash = currentDash;
		ResetFrameFlip();
		return FALSE;
	}
	// đã có thể dash
	if (currentDash == this->befDash && this->frameFlip <= MAX_FRAME_FLIP) {
		this->frameFlip = 0;
		this->befDash = BeforeDash::None;
		ResetFrameFlip();
		return TRUE;
	}
	// nhấn phím quá chậm
	this->frameFlip = 0;
	return FALSE;
}


void PlayerStandingState::ResetFrameFlip() {
	this->frameFlip = 0;
	this->flipStart = TRUE;
}

void PlayerStandingState::StopFrameFlip() {
	this->frameFlip = 0;
	this->flipStart = FALSE;
	this->befDash = BeforeDash::None;
}

void PlayerStandingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
	}

	if (object->type == Type::BULLETTYPE) {
		auto castBullet = (Bullet*)object;
		
		if (player->GetMoveDirection() != castBullet->GetMoveDirection() && !castBullet->CanGetThroughShield()) {
			return;
		}

		player->OnCollisionWithBullet(castBullet);
	}
}
