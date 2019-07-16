#include"PlayerStandingState.h"

PlayerStandingState::PlayerStandingState()
{
	//Player::getInstance()->state = standing;
	state = STANDING;
}

void PlayerStandingState::Update(float dt)
{
	this->InputHandler();
	Player::getInstance()->curanimation->Update(dt);
}

void PlayerStandingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();

	if (player == NULL || keyboard == NULL)
		return;

	// di chuyển qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		player->SetVx(-PLAYER_NORMAL_SPEED);
		player->ChangeState(State::RUNNING);
		return;
	}
	// di chuyển qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		player->SetVx(PLAYER_NORMAL_SPEED);
		player->ChangeState(State::RUNNING);
		return;
	}
	// nhảy lên
	if (keyboard->isKeyDown(PLAYER_JUMP)) {
		player->ChangeState(State::JUMPING);
		player->SetAirState(Player::OnAir::Jumping);
		player->SetVy(PLAYER_NORMAL_SPEED);
		return;
	}
}

void PlayerStandingState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;
	
	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::bottom) {
			Player::getInstance()->SetAirState(Player::OnAir::None);
		}
	}
}