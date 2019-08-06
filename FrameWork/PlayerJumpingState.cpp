#include "PlayerJumpingState.h"
#include"Debug.h"
#include "SceneManager.h"


void PlayerJumpingState::InputHandler() {
	auto player = Player::getInstance();	
	auto keyboard = KeyboardManager::getInstance();
	int timePressedJump = 0;
	if (player == NULL || keyboard == NULL)
		return;

	// xét thời gian đã press phím jump
	if (player->GetOnAirState() == Player::OnAir::Jumping) {
		this->curDelayTime = 0;
		 //phím Jump đã được nhấn từ trước
		if (!keyboard->getKeyPressedOnce(PLAYER_JUMP, timePressedJump) && timePressedJump > 0) {
			player->OnJumping(timePressedJump / 10);
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

	// va chạm với ground
	if (object->type == Type::GROUND || object->type == Type::PLATFORM) { 
		if (side == CollisionSide::bottom ) {
 			player->OnStandingOnGround(object);
			DebugOut(L"\nState Now: ");
			PrintDebugNumber(player->state);
			return;
		}
	}
	 
	// va chạm với nước
	if (object->type == Type::WATERRL) {
		if ( (player->GetPreviousState() != nullptr) && (player->GetPreviousState()->state == State::FLOATING))
			return;
		player->OnCollisionWithWater(object, collision);
		return;
	}

	// đang nhảy va chạm với solid box
	if (object->type == Type::SOLIDBOX) {
		player->OnCollisionWithSolidBox(object, collision);
		return;
	}

	if (object->type == Type::ROPE) {
		PlayerHandOnRope* handOnRope = new PlayerHandOnRope();
		SceneManager::getInstance()->AddObjectToCurrentScene(handOnRope);
		return;
	}

	if (object->type == Type::BULLETTYPE) {
		player->OnCollisionWithEnemy(object);
		return;
	}

	if (object->type == Type::SPIKE) {
		if (side == CollisionSide::bottom) {
			if (player->IsNonAttackable()) {
				player->OnStandingOnGround(object);
			}
			else {
				player->OnCollisionWithSpike(object);
			}
		}
	}
 }
