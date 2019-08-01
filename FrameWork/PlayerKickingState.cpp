#include "PlayerKickingState.h"
#include"Debug.h"


PlayerKickingState::PlayerKickingState()
{
	state = State::KICKING;
	this->curKickTime = 0;
}


PlayerKickingState::~PlayerKickingState()
{
}

void PlayerKickingState::InputHandler()
{
	Player* player = Player::getInstance();
	auto keyboard = KeyboardManager::getInstance();
	
	if (this->curKickTime > MAX_KICKING_TIME) {
		// trạng thái trước đó là ROLLING thì chuyển về lại ROLLING
		if (player->GetPreviousState()->state == State::ROLLING)
			player->ChangeState(State::ROLLING);
		else
			player->ChangeState(State::JUMPING);
		this->curKickTime = 0;
		return;
	}

	//int timePressedJump = 0;
	//// xét thời gian đã press phím jump
	//if (player->GetOnAirState() == Player::OnAir::Jumping) {
	//	//phím Jump đã được nhấn từ trước
	//	if (!keyboard->getKeyPressedOnce(PLAYER_JUMP, timePressedJump) && timePressedJump > 0) {
	//		//chuyển sang trạng thái roll
	//		if (timePressedJump / 10 > MAX_KICKING_TIME) {
	//			player->ChangeState(State::ROLLING);
	//			return;
	//		}
	//		player->SetVy(player->vy + 0.15);
	//	}
	//}

	//  Đổi hướng qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetMoveDirection(Player::MoveDirection::RightToLeft);
	}

	// Đổi hướng qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
		player->SetMoveDirection(Player::MoveDirection::LeftToRight);
	}

	this->curKickTime++;

}



void PlayerKickingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND) {
		// chạm vào ground trên đầu
		if (side == CollisionSide::top) {
			//player->SetVy(0);
		}
		else {
			// chạm nền dưới
			if (side == CollisionSide::bottom ) {
				player->OnStandingOnGround(object);
				DebugOut(L"\nState Now:\n");
				PrintDebugNumber(player->state);
			}
		}
	}
	if (object->type == Type::WATERRL) {
		player->OnCollisionWithWater(object, collision);
		return;
	}

	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
		return;
	}

	if (object->type == Type::ENEMY) {
		player->OnCollisionWithEnemy(object);
	}
}

void PlayerKickingState::Update(float dt)
{
	this->InputHandler();
}

