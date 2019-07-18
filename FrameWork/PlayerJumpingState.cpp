#include "PlayerJumpingState.h"
#include"Debug.h"
void PlayerJumpingState::InputHandler() {

	auto player = Player::getInstance();	
	auto keyboard = KeyboardManager::getInstance();
	int timePressedJump = 0;
	if (player == NULL || keyboard == NULL)
		return;

	// xét thời gian đã press phím jump
	if (player->GetOnAirState() == Player::OnAir::Jumping && !keyboard->getKeyPressedOnce(PLAYER_JUMP, timePressedJump)) {

		if (player->GetOnAirState() == Player::OnAir::Falling)
			goto SkipPlayerJump;

  		if (timePressedJump <=0)
			goto SkipPlayerJump;
		// nhảy cấp độ 1
		if (timePressedJump <= MIN_TIME_JUMP_1) {
			player->SetVy(player->vy + ADDED_SPEED);
		}
		else {
			// nhảy cấp độ 2
			if (timePressedJump <= MIN_TIME_JUMP_2) {
				player->SetVy(player->vy + ADDED_SPEED);
			}
			//chuyển sang trạng thái roll
			else 
			{
				player->ChangeState(State::ROLLING);
			}
		}
	}

SkipPlayerJump:
	// Nhấn phím tấn công thì chuyển sang trạng thái đá
	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		player->ChangeState(State::KICKING);
		return;
	}
	// nhảy và chạy qua phải
	if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
		player->SetVx(PLAYER_NORMAL_SPEED);
		goto SetAirState;
	}
		// nhảy và chạy qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetVx(-PLAYER_NORMAL_SPEED);
	}

SetAirState:
	// nhảy tới khi vận tốc bằng 0 thì AirState là rơi xuống
	if (player->GetOnAirState() == Player::OnAir::Jumping && player->vy <= 0) {
		player->SetVy(0);
		return;
	}
	if (player->GetOnAirState() == Player::OnAir::Falling && player->pos.y <= 60) {
		player->ChangeState(State::STANDING);
		player->pos.y = 60;
		return;
	}


}

void PlayerJumpingState::Update(float dt) {

	this->InputHandler();
}

void PlayerJumpingState::OnCollision(Object* object, collisionOut* collision) {
	//auto player = Player::getInstance();
	//auto side = collision->side;

	//if (object->type == Type::GROUND) {
	//	// chạm vào ground trên đầu
	//	if (side == CollisionSide::top) {
	//		//player->SetVy(0);
	//	}
	//	else {
	//		// chạm nền dưới
	//		if (side == CollisionSide::bottom && player->GetOnAirState() == Player::OnAir::Falling)
	//		{
	//			player->pos.y += player->vy * collision->collisionTime + object->height / 2;
	//			player->ChangeState(State::STANDING);
	//		}
	//	}
	//}
}

BoundingBox PlayerJumpingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y + 20;
	box.bottom = player->pos.y - 18;
	box.left = player->pos.x - 11;
	box.right = player->pos.x + 11;
	return box;
}