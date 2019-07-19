#include "PlayerJumpingState.h"
#include"Debug.h"
void PlayerJumpingState::InputHandler() {
	auto player = Player::getInstance();	
	auto keyboard = KeyboardManager::getInstance();
	int timePressedJump = 0;
	if (player == NULL || keyboard == NULL)
		return;

	// xét thời gian đã press phím jump
	if (player->GetOnAirState() == Player::OnAir::Jumping) {
		// phím Jump đã được nhấn từ trước
		if (!keyboard->getKeyPressedOnce(PLAYER_JUMP, timePressedJump) && timePressedJump != -1) {
			if (timePressedJump <= MIN_TIME_JUMP_2) {
				player->SetVy(player->vy + ADDED_SPEED);
				return;
			}
			//chuyển sang trạng thái roll
			else
			{
				player->ChangeState(State::ROLLING);
				return;
			}
		}

		if (keyboard->isKeyDown(PLAYER_JUMP)) {
			player->SetVy(player->vy + ADDED_SPEED);
			return;
		}

		// nhảy cấp độ 1

	}

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
	else {
		player->SetVx(0);
	}
		// nhảy và chạy qua trái
	if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetVx(-PLAYER_NORMAL_SPEED);
		goto SetAirState;
	}
	else {
		player->SetVx(0);
	}

SetAirState:
	// nhảy tới khi vận tốc bằng 0 thì AirState là rơi xuống
	if (player->IsReachMaxJump()) {
		player->SetVy(0);
		return;
	}
}

void PlayerJumpingState::Update(float dt) {

	this->InputHandler();
}

void PlayerJumpingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND) { 
		player->SetGroundCollision(new GroundCollision(object, side));
		// chạm vào ground trên đầu
		if (side == CollisionSide::top) {
			//player->SetVy(0);
		}
		else {
			// chạm nền dưới
			if (side == CollisionSide::bottom ) {
				if (collision->side == CollisionSide::bottom)
				{
					DebugOut(L"\nJump Bottom");
				}
				player->ChangeState(State::STANDING);	
				player->pos.y = object->pos.y + player->getHeight() / 2;
			}
		}
	}
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