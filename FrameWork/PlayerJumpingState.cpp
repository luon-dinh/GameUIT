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
		 //phím Jump đã được nhấn từ trước
		if (!keyboard->getKeyPressedOnce(PLAYER_JUMP, timePressedJump) && timePressedJump > 0) {
			if (timePressedJump / 10 < MIN_TIME_JUMP_1) {
				return;
			}
			else
				if (timePressedJump / 10 < MIN_TIME_JUMP_2) {
         			player->SetVy(player->vy + ADDED_SPEED_1);
				}
				else {
					if (timePressedJump / 10 < MIN_TIME_ROLL) {
						player->SetVy(player->vy + ADDED_SPEED_2);
					}
					else {
						//chuyển sang trạng thái roll
						player->ChangeState(State::ROLLING);
						return;
					}
				}
		}
	}
	// Nhấn phím tấn công thì chuyển sang trạng thái đá
	if (keyboard->getKeyPressedOnce(PLAYER_ATTACK)) {
		player->ChangeState(State::KICKING);
		return;
	}
	if (!keyboard->isKeyDown(PLAYER_MOVE_RIGHT) && !keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
		player->SetVx(0);
	}
	else {
		if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT)) {
			player->SetVx(PLAYER_NORMAL_SPEED);
		}
		else{
			if (keyboard->isKeyDown(PLAYER_MOVE_LEFT)) {
				player->SetVx(-PLAYER_NORMAL_SPEED);
			}
		}
	}
}

void PlayerJumpingState::Update(float dt) {
	this->InputHandler();
}

void PlayerJumpingState::OnCollision(Object* object, collisionOut* collision) {
	auto player = Player::getInstance();
	auto side = collision->side;

	if (object->type == Type::GROUND && player->GetOnAirState() != Player::OnAir::DropToWater) { 
		
		// chạm vào ground trên đầu
		if (side == CollisionSide::top) {
			//player->SetVy(0);
		}
		else {
			// chạm nền dưới
			if (side == CollisionSide::bottom ) {
				player->SetGroundCollision(new GroundCollision(object, side));
				player->ChangeState(State::STANDING);	
				player->pos.y = object->pos.y + player->getHeight() / 2;
				DebugOut(L"\nState Now: ");
				PrintDebugNumber(player->state);
			}
		}
		return;
	}

	// va chạm với nước
	if (object->type == Type::WATERRL) {
		player->HandleWaterCollision(object, collision);
		return;
	}

	if (object->type == Type::SOLIDBOX) {
		if (player->GetOnAirState() != Player::OnAir::Falling && player->GetOnAirState() != Player::OnAir::DropToWater) {
			player->SetAirState(Player::OnAir::Falling);
			player->SetVx(0);
		}
	}
 }

BoundingBox PlayerJumpingState::getBoundingBox()
{
	Player *player = Player::getInstance();
	BoundingBox box;
	box.vx = player->vx;
	box.vy = player->vy;
	box.top = player->pos.y -7;
	box.bottom = player->pos.y - 15;
	box.left = player->pos.x - 11;
	box.right = player->pos.x + 11;
	return box;
}