#include "PlayerRunningState.h"
#include"Debug.h"


PlayerRunningState::PlayerRunningState()
{
	state = RUNNING;
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
	int timePressedMove = 0;

	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
	{
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
		if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
			return;
		}
		if (keyboard->getKeyPressedOnce	(PLAYER_ATTACK)) {
			// nếu đang có shield thì chuyển qua trạng thái shield attack
			if (player->hasShield) {
				player->ChangeState(State::SHIELD_ATTACK);
			}
			else {
				player->ChangeState(State::STAND_PUNCH);
			}
		}
		if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
			player->ChangeState(State::STANDING);
		return;
	}

	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT))
	{
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
		if (keyboard->getKeyPressedOnce(PLAYER_JUMP)) {
			player->ChangeState(State::JUMPING);
			return;
		}
		if (keyboard->isKeyDown(PLAYER_ATTACK)) {
			// nếu đang có shield thì chuyển qua trạng thái shield attack
			if (player->hasShield) {
				player->ChangeState(State::SHIELD_ATTACK);
			}
			else {
				player->ChangeState(State::STAND_PUNCH);
			}
		}
		if (keyboard->isKeyDown(PLAYER_MOVE_LEFT))
			player->ChangeState(State::STANDING);
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
		if (side == CollisionSide::bottom)
		{
			player->OnStandingOnGround(object);
			DebugOut(L"\nRunning Bottom");
		}
		return;
	}

	// đang nhảy va chạm với solid box
	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
	}


	if (object->type == Type::BULLETTYPE) {
		auto castBullet = (Bullet*)object;
		if (player->hasShield) {
			if (castBullet->GetMoveDirection() != player->GetMoveDirection() && !castBullet->CanGetThroughShield()) {
				return;
			}
		}
		player->OnCollisionWithBullet(castBullet);
	}
}




void PlayerRunningState::Update(float dt)
{
	this->InputHandler();
}
