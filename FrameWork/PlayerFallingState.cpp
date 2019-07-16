#include "PlayerFallingState.h"



PlayerFallingState::PlayerFallingState()
{
	state = State::FALLING;
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	this->InputHandler();
	Player* player = Player::getInstance();
	player->pos.y = player->pos.y + player->vy;
	player->vy -= 0.035;
	Player::getInstance()->curanimation->Update(dt);
}

void PlayerFallingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	if (player == NULL || keyboard == NULL)
		return;

	if (keyboard->isKeyDown(PLAYER_JUMP))
	{
		player->SetVy(10);
		player->AddPosY();
		return;
	}
	if (keyboard->isKeyDown(DIK_DOWN))
	{
		player->SetVy(-10);
		player->AddPosY();
		return;
	}
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		player->SetVx(-10);
		player->ChangeState(State::RUNNING);
		return;
	}
	if (KeyboardManager::getInstance()->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		player->SetVx(10);
		player->ChangeState(State::RUNNING);
		return;
	}
}

void PlayerFallingState::OnCollision(Object* object, collisionOut* collision) {
	auto side = collision->side;

	// collide with ground
	if (object->type == Type::GROUND) {
		if (side == CollisionSide::bottom) {
			Player *player = Player::getInstance();
			player->SetVy(0);
			player->vy = 0;
			player->ChangeState(State::STANDING);
		}
	}
}