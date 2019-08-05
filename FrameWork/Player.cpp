#include"Player.h"
#include"Camera.h"
#include"Debug.h"
#include "SceneManager.h"

Player* Player::instance = NULL;

Player::Player() : GamePlayerProperty()
{
	LoadAllAnimations();
	LoadAllStates();

	this->pos.x = 30;
	this->pos.y = 80;
	this->tag = Tag::PLAYER;
	this->type = Type::NONE;
	this->vx = 0;
	this->vy = 0;
	this->direction = MoveDirection::LeftToRight;

	this->state = State::JUMPING;
	this->playerstate = playerStates[State::JUMPING];
	this->curanimation = animations[this->state];
	this->prevState = NULL;
	this->collisionAffect = TRUE;
	this->detectRopeCollision = false;
	this->SetMoveProperty(MoveProperties::StoppedBySolidBox);

	this->flipRenderFrame = 0;

	this->SetHeart(4);
}

PlayerState* Player::GetPreviousState() {
	return this->prevState;
}

void Player::SetPreviousState(State stateName) {
	this->prevState = playerStates[stateName];
}

void Player::LoadAllAnimations() {
	animations[STANDING] = new Animation(PLAYER, 0, 1);
	animations[RUNNING] = new Animation(PLAYER, 1, 5);
	animations[SHIELD_UP] = new Animation(PLAYER, 5, 6);
	animations[DUCKING] = new Animation(PLAYER, 6, 7);
	animations[JUMPING] = new Animation(PLAYER, 7, 8);
	animations[ROLLING] = new Animation(PLAYER, 8, 12);
	animations[KICKING] = new Animation(PLAYER, 12, 13);
	animations[SHIELD_ATTACK] = new Animation(PLAYER, 13, 15);
	animations[STAND_PUNCH] = new Animation(PLAYER, 15, 17);
	animations[DUCKING_PUNCHING] = new Animation(PLAYER, 17, 19);
	animations[DASHING] = new Animation(PLAYER, 19, 22);
	animations[SHIELD_DOWN] = new Animation(PLAYER, 22, 23);
	animations[CLIMBING] = new Animation(PLAYER, 23, 26);
	animations[FLOATING] = new Animation(PLAYER, 28, 37);
	animations[DIVING] = new Animation(PLAYER, 37, 39);
	animations[BEATEN] = new Animation(PLAYER, 26, 27);
	animations[FLYING_BEATEN] = new Animation(PLAYER, 39, 40);
	animations[DEAD] = new Animation(PLAYER, 27, 28);
	animations[SHOCKING] = new Animation(PLAYER, 42, 44);
}

void Player::LoadAllStates() {
	this->playerStates[State::STANDING] = new PlayerStandingState();
	this->playerStates[State::RUNNING] = new PlayerRunningState();
	this->playerStates[State::JUMPING] = new PlayerJumpingState();
	this->playerStates[State::DUCKING] = new PlayerSittingState();
	this->playerStates[State::DUCKING_PUNCHING] = new PlayerDuckingPunchingState();
	this->playerStates[State::SHIELD_UP] = new PlayerShieldUpState();
	this->playerStates[State::KICKING] = new PlayerKickingState();
	this->playerStates[State::ROLLING] = new PlayerRollingState();
	this->playerStates[State::DASHING] = new PlayerDashingState();
	this->playerStates[State::FLOATING] = new PlayerFloatingState();
	this->playerStates[State::DIVING] = new PlayerDivingState();
	this->playerStates[State::SHIELD_DOWN] = new PlayerShieldDownState();
	this->playerStates[State::SHIELD_ATTACK] = new PlayerShieldAttackState();
	this->playerStates[State::STAND_PUNCH] = new PlayerStandPunchState();
	this->playerStates[State::CLIMBING] = new PlayerClimbingState();
	this->playerStates[State::BEATEN] = new PlayerBeatenState();
	this->playerStates[State::FLYING_BEATEN] = new PlayerFlyingBeatenState();
	this->playerStates[State::DEAD] = new PlayerDyingState();
	this->playerStates[State::SHOCKING] = new PlayerShockingState();
}




Player::~Player()
{

}

float Player::getPosToBotom()
{
	auto sprite = this->curanimation->getSprite(curanimation->curframeindex);
	RECT rect = sprite->getRECT();
	return (rect.top + rect.bottom) / 2 - rect.bottom;
}

BoundingBox Player::getBoundingBox()
{
	auto sprite = this->curanimation->getSprite(curanimation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	height = rect.top - rect.bottom;
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	box.top = this->pos.y + height / 2;
	box.left = this->pos.x - width / 2;
	box.bottom = this->pos.y - height / 2;
	box.right = this->pos.x + width / 2;
	if (this->state == State::DUCKING_PUNCHING)
	{
		switch (this->direction)
		{
		case MoveDirection::LeftToRight:
			box.left = this->pos.x - this->width / 2; 
			box.right = this->pos.x;
			break;
		case MoveDirection::RightToLeft:
			box.left = this->pos.x;
			box.right = this->pos.x + this->width / 2;
			break;
		default:
			break;
		}
		return box;
	}
	if (this->state == State::STAND_PUNCH)
	{
		switch (this->direction)
		{
		case MoveDirection::LeftToRight:
			box.left = this->pos.x - this->width / 2;
			box.right = this->pos.x ;
			break;
		case MoveDirection::RightToLeft:
			box.left = this->pos.x;
			box.right = this->pos.x + this->width / 2;
			break;
		default:
			break;
		}
		return box;
	}
	if (this->state == State::KICKING)
	{
		switch (this->direction)
		{
		case MoveDirection::LeftToRight:
			box.right = this->pos.x - 4;
			box.left = this->pos.x - 20;
			break;
		case MoveDirection::RightToLeft:
			box.left = this->pos.x + 4;
			box.right = this->pos.x + 20;
			break;
		default:
			break;
		}
		
		return box;
	}

	return box;
}

void Player::Update(float dt)
{
	// Update state
	this->playerstate->Update(dt);

	// update các thuộc tính của game
	this->UpdateGameProperty();
	// update máu để render
	HealthPoint::getInstance()->Update(this->GetHeart());

	if (this->IsDead() && this->GetOnAirState() == OnAir::None) {
		this->ChangeState(State::DEAD);
	}

	UpdatePosition();

	if (this->IsOnPlatform()) {
		auto platform = this->GetStandingGround();
		this->pos.x += platform->vx;
		this->pos.y = platform->getBoundingBox().top + this->getHeight() / 2 - 2;
	}

	// Update animation
	this->curanimation->Update(dt);

}

void Player::Render()
{
	HealthPoint::getInstance()->Render();
	ExitSignal::getInstance()->Render();
	// Đang không ở trạng thâí vô địch thì render như thường
	if (!this->IsNonAttackable()) {
		InnerRender();
	}
	else {
		this->flipRenderFrame++;
		if (this->flipRenderFrame < FLIP_RENDER_FRAME / 2) {
			// do nothing here
		}
		else {
			InnerRender();
			if (this->flipRenderFrame == FLIP_RENDER_FRAME) {
				this->flipRenderFrame = 0;
			}
		}
	}

}

void Player::InnerRender() {
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, pos.y, 0));
	if (this->direction == Player::MoveDirection::LeftToRight) {
		// move from left to right
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal);
	}
	else {
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
	}
}


Player* Player::getInstance()
{
	if (!instance)
		instance = new Player();
	return instance;
}


void Player::ChangeState(PlayerState* newplayerstate)
{
	delete playerstate;
	playerstate = newplayerstate;
	playerstate->state = newplayerstate->state;
	curanimation = animations[playerstate->state];
	this->state = playerstate->state;
}

int Player::GetDamage() {
	switch (this->state) {
		case State::DASHING:			
		case State::SHIELD_DOWN:		SetDamage(6);break;
		case State::STAND_PUNCH: 
		case State::DUCKING_PUNCHING:  
		case State::ROLLING:
		case State::KICKING:			SetDamage(2);break;
		case State::BEATEN:
		case State::FLYING_BEATEN:		SetDamage(0);break;
		default:
			SetDamage(1);
	}
	return this->damage;
}

int Player::GetCollisionDamage() {
	return this->GetDamage();
}

bool Player::IsNonAttackable() {
	this->isCollidable = false;
	if (GamePlayerProperty::IsNonAttackable()) {
		this->isCollidable = false;
		return true;
	}
	this->isCollidable = true;
	return false;
}

bool Player::IsImmortal() {
	if (GamePlayerProperty::IsImmortal()) {
		this->isCollidable = false;
		return true;
	}
	this->isCollidable = true;
	return false;
}

void Player::ChangeState(State stateName) {
	if (this->state == stateName)
		return;
	// nếu đang bất tử thì chuyển sang normal
	if (this->state == State::ROLLING) {
		this->SetToNormalState();
	}
	float PosToBottom1 = this->getPosToBotom();
	InnerChangeState(stateName);
	auto shield = Shield::getInstance();
	float PosToBottom2 = this->getPosToBotom();
	this->pos.y = this->pos.y + (PosToBottom2 - PosToBottom1);

	// thay đổi riêng biệt cho từng loại state
	switch (stateName) {
	case State::STANDING: {
		if(this->onAirState ==OnAir::Falling)
			SoundManager::getinstance()->play(SoundManager::SoundName::player_stand);
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::Defense);
		}
		this->SetOnAirState(Player::OnAir::None);
		this->SetVx(0);
		break;
	}
	case State::RUNNING: {
		this->SetOnAirState(Player::OnAir::None);
		if (this->direction == MoveDirection::LeftToRight)
			SetVx(PLAYER_NORMAL_SPEED);
		else {
			SetVx(-PLAYER_NORMAL_SPEED);
		}
		break;
	}
	case State::JUMPING: {
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::Transparent);
		}
		// nếu trước đó đang falling tiếp tục là falling
		if (this->onAirState == OnAir::Falling || this->onAirState == OnAir::DropToWater) {
			return;
		}
		if (this->onAirState == OnAir::Jumping)
			return;
		if (this->prevState->state == State::FLOATING) {
			shield->SetShieldState(Shield::ShieldState::Transparent);
			this->SetOnAirState(OnAir::JumpFromWater);
			return;
		}
		this->SetOnAirState(OnAir::Jumping);
		this->SetStandingGround(NULL);
		break;
	}
	case State::DASHING: {
		SoundManager::getinstance()->play(SoundManager::SoundName::player_dash);
		// dash khi có shield thì shield k render, ngược lại nghĩa là shield đang ở trạng thái attack
		if (this->hasShield)
			shield->SetShieldState(Shield::ShieldState::Transparent);
		if (this->direction == MoveDirection::LeftToRight) {
			SetVx(PLAYER_DASH_SPEED);
		}
		else {
			SetVx(-PLAYER_DASH_SPEED);
		}
		break;
	}
	case State::DIVING: {
		SoundManager::getinstance()->play(SoundManager::SoundName::player_diving);
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::NotRender);
		}
		break;
	}
	case State::FLOATING: {
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::NotRender);
		}
		this->SetOnAirState(OnAir::None);
		this->vx = -WATER_SPEED;
		break;
	}
	case State::ROLLING: {
		SoundManager::getinstance()->play(SoundManager::SoundName::player_rolling);
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::NotRender);
		}
		this->SetToImmortalState();
		break;
	}
	case State::KICKING: {
		SoundManager::getinstance()->play(SoundManager::SoundName::player_punch_kick);
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::Transparent);
		}
		PlayerKickPart* kickPart = new PlayerKickPart();
		SceneManager::getInstance()->AddObjectToCurrentScene(kickPart);
		break;
	}
	case State::SHIELD_DOWN: {
		shield->SetShieldState(Shield::ShieldState::Defense);
		break;
	}
	case State::SHIELD_ATTACK: {
		SoundManager::getinstance()->play(SoundManager::SoundName::shield_attack);
		SetVx(0);
		shield->SetShieldState(Shield::ShieldState::Transparent);
		break;
	}
	case State::STAND_PUNCH: {
		SoundManager::getinstance()->play(SoundManager::SoundName::player_punch_kick);
		SetVx(0);
		PlayerHandPunch* handPunch = new PlayerHandPunch();
		SceneManager::getInstance()->AddObjectToCurrentScene(handPunch);
		break;
	}
	case State::DUCKING_PUNCHING: {
		SoundManager::getinstance()->play(SoundManager::SoundName::player_punch_kick);
		PlayerHandPunch* handPunch = new PlayerHandPunch();
		SceneManager::getInstance()->AddObjectToCurrentScene(handPunch);
		return;
	}
	case State::DUCKING: {
		SetVx(0);
		break;
	}
	case State::CLIMBING: {
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::Transparent);
		}
		this->SetOnAirState(OnAir::HangOnTheRope);
		break;
	}
	case State::BEATEN: {
		this->SetVx(0);
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::NotRender);
		}
		return;
	}
	case State::FLYING_BEATEN: {
		this->SetVx(0);
		this->SetOnAirState(OnAir::Falling);
		if (this->hasShield) {
			shield->SetShieldState(Shield::ShieldState::NotRender);
		}
		return;
	}
	case State::DEAD: {
		//SoundManager::getinstance()->play(SoundManager::SoundName::player_dead); chờ nào dead thật thì play
		this->SetActive(false);
		shield->SetShieldState(Shield::ShieldState::NotRender);
		this->SetToNonAttackableState(300);
		return;
	}
	case State::SHOCKING: {
		shield->SetShieldState(Shield::ShieldState::NotRender);
		this->SetToNonAttackableState();
		return;
	}
	}
}

BOOL Player::IsReachMaxJump() {
	return this->vy <= 0 && this->onAirState == OnAir::Jumping;
}

bool Player::IsFootStepOn() {
	return this->currentGround->type == Type::GROUND || this->currentGround->type == Type::SOLIDBOX;
}

bool Player::IsOnPlatform() {
	auto ground = this->GetStandingGround();
	return ground != NULL && ground->type == Type::PLATFORM;
}


void Player::SetShieldReturnEdge(Player::ShieldReturnEdge edge) {
	this->edge = edge;

	switch (edge) {
	case Player::ShieldReturnEdge::Bottom: {
		SetShieldReturnPos(this->pos.x, this->pos.y - this->getHeight() / 2);break;
	}
	case Player::ShieldReturnEdge::Top: {
		SetShieldReturnPos(this->pos.x, this->pos.y + this->getHeight() / 2);break;
	}
	case Player::ShieldReturnEdge::Left: {
		SetShieldReturnPos(this->pos.x - this->getWidth() / 2, this->pos.y);break;
	}
	case Player::ShieldReturnEdge::Right: {
		SetShieldReturnPos(this->pos.x + this->getWidth() / 2, this->pos.y);break;
	}
	case Player::ShieldReturnEdge::Default: {
		SetShieldReturnPos(this->pos.x, this->pos.y);break;
	}
	}
}

Player::ShieldReturnEdge Player::GetShieldReturnEdge() {
	return this->edge;
}

D3DXVECTOR2 Player::GetShieldReturnPos() {
	switch (this->state) {
	case State::DASHING:
	case State::RUNNING:
	case State::STANDING:
	case State::STAND_PUNCH:
	case State::JUMPING:
	case State::DUCKING_PUNCHING:
	case State::DUCKING:
		SetShieldReturnEdge(ShieldReturnEdge::Default);break;
	case State::ROLLING:
	case State::SHIELD_DOWN:
	case State::FLOATING:
	case State::DIVING:
		SetShieldReturnEdge(ShieldReturnEdge::Bottom);break;
	}
	return this->shieldReturnPos;
}

void Player::SetShieldReturnPos(float x, float y) {
	this->shieldReturnPos.x = x;
	this->shieldReturnPos.y = y;
}

void Player::Float(MoveDirection moveDir) {
	// nếu không ở trạng thái nổi thì thoát
	if (this->playerstate->state != State::FLOATING)
		return;

	this->direction = moveDir;

	if (this->direction == MoveDirection::LeftToRight) {
		// bơi từ trái qua phải thì trừ đi v của nước
		this->vx = PLAYER_NORMAL_SPEED - WATER_SPEED;
	}
	else {
		this->vx = -PLAYER_NORMAL_SPEED - WATER_SPEED;
	}

}

void Player::InnerChangeState(State stateName) {
	SetPreviousState(this->state);
	this->state = stateName;
	this->playerstate = playerStates[stateName];
	curanimation = animations[stateName];
}

void Player::SetVx(float vx) {
	Object::SetVx(vx);
	if (!this->hasShield)
		return;
	Shield::getInstance()->SetMoveDirection(this->direction);
}


void Player::SetVx(float vx, BOOL changePlayerDirection) {
	if (changePlayerDirection) {
		SetVx(vx);
		return;
	}
	this->vx = vx;
}


void Player::AddPosX() {
	this->vx += this->accelerator.x;
	this->pos.x += this->vx;
}

void Player::AddPosY() {
	if (this->vy <= -5)
		this->accelerator.y = 0;
	this->SetVy(this->vy + this->accelerator.y);
	this->pos.y += this->vy;
}

void Player::UpdatePosition() {
	this->accelerator.x = 0;
	if (!this->IsStopBySolidBox()) {
		AddPosX();
	}
	AddPosY();


}

void Player::SetMoveDirection(MoveDirection moveDir) {
	Object::SetMoveDirection(moveDir);

	//auto shield = Shield::getInstance();
	//shield->SetMoveDirection(this->direction);
}

BOOL Player::GetCollisionAffect() {
	return this->collisionAffect;
}

void Player::SetCollisionAffect(BOOL value) {
	this->collisionAffect = value;
}

void Player::SetOnAirState(OnAir onAirState) {
	Object::SetOnAirState(onAirState);

	switch (this->onAirState) {
		case OnAir::None: {
			this->accelerator.y = 0;
			this->vy = 0;
			return;
		}
		case OnAir::Jumping: {
			this->accelerator.y = -GROUND_GRAVITY;
			this->vy = PLAYER_JUMP_SPEED;
			return;
		}
		case OnAir::DropToWater: {
			this->vy = -2;
			return;
		}
		case OnAir::Falling: {
			this->accelerator.y = -GROUND_GRAVITY;
			return;
		}
		case OnAir::JumpFromWater: {
			this->vy = 5;
			this->accelerator.y = -0.2;
			return;
		}
		case OnAir::HangOnTheRope: {
			this->vy = this->vx = 0;
			this->SetAccelerate(D3DXVECTOR2(0, 0));
			return;
		}
		case OnAir::FloatAboveWater: {
		this->vx = this->vy = 0;
		this->accelerator = D3DXVECTOR2(0, 0);
		return;
	}
	}
}


float Player::getWidth()
{
	auto sprite = this->curanimation->getSprite(curanimation->curframeindex);
	RECT rect = sprite->getRECT();
	return rect.right - rect.left;
}

float Player::getHeight()
{
	auto sprite = this->curanimation->getSprite(curanimation->curframeindex);
	RECT rect = sprite->getRECT();
	return rect.top - rect.bottom;
}

void Player::OnJumping(int frames) {
	if (frames < MIN_TIME_JUMP_1) {
		// do nothing here
		return;
	}
	else
		if (frames  < MIN_TIME_JUMP_2) {
			this->SetVy(this->vy + ADDED_SPEED_1);
		}
		else {
			if (frames < MIN_TIME_ROLL) {
				this->SetVy(this->vy + ADDED_SPEED_2);
			}
			else {
				if (frames < MAX_TIME_JUMP) {
					//chuyển sang trạng thái roll
					this->ChangeState(State::ROLLING);
				}
			}
		}
}


#pragma region Collison Handler Implementation
void Player::OnCollision(Object* object, collisionOut* collisionOut) {
	// không xét va chạm với shield
	if (object->tag == Tag::SHIELD)
		return;
	// gọi tới hàm va chạm của state
	this->playerstate->OnCollision(object, collisionOut);
}
void Player::OnNotCollision(Object* object) {
	switch (object->type) {
	case Type::PLATFORM:
	case Type::GROUND: {
		// nếu đang ở trạng thái rơi xuống nước thì bỏ qua va chạm với ground
 		if (this->GetOnAirState() == OnAir::DropToWater) {
			return;
		}
		//Trong trường hợp đã rơi khỏi ground hiện tại
		if (this->GetOnAirState() == OnAir::None) {
			if (this->StandOnCurrentGround() == FALSE && this->GetStandingGround() != NULL) {
				this->OnFallingOffGround();
				return;
			}
		}
		break;
	}
	case Type::SOLIDBOX: {
		if (object == this->collidedSolidBox) {
			this->smashLeft = this->smashRight = false;
		}
		if (object == this->GetStandingGround()) {
			if (!this->StandOnCurrentGround()) {
				this->OnFallingOffGround();
				return;
			}
		}
	}
	}
}
bool Player::OnRectCollided(Object* object, CollisionSide side) {

	//if (this->state == State::DASHING && (side == CollisionSide::left || side == CollisionSide::right))
	//{
	//	// collide with ground
	//	this->ChangeState(State::STANDING);
	//	switch (side)
	//	{
	//	case CollisionSide::left:
	//		this->ChangeState(State::STANDING);
	//		this->pos.x = object->getBoundingBox().right + this->getWidth() / 2 + 4;
	//		break;
	//	case CollisionSide::right:
	//		this->pos.x = object->getBoundingBox().left - this->getWidth() / 2 - 4;
	//		break;
	//	default:
	//		break;
	//	}
	//	return true;
	//}
	//SoundManager::getinstance()->play(SoundManager::SoundName::stage2, false);
	auto box = this->getBoundingBox();
	auto bound = object->getBoundingBox();
	switch (object->type) {
		case Type::PLATFORM:
		case Type::GROUND: {
  			if (this->GetOnAirState() == OnAir::DropToWater)
				return false;
			if (this->GetOnAirState() == OnAir::Falling) {
				// nếu trạng thái trước đó là none thì bỏ qua xét va chạm rect với GROUND
				if (this->GetPreOnAirState() == OnAir::None)
					return false;
				this->TryStandOnGround(object);
				return true;
			}
			return false;
		}
		case Type::WATERRL: {
			if (this->GetOnAirState() == OnAir::JumpFromWater) {
				return false;
			}
			if (this->GetOnAirState() == OnAir::Falling) {
				collisionOut colOut;
				colOut.side = CollisionSide::bottom;
				this->OnCollisionWithWater(object, &colOut);
			}
			return false;
		}
		case Type::SOLIDBOX: {
			BoundingBox box = this->getBoundingBox();
			BoundingBox bound = object->getBoundingBox();
			if (this->collidedSolidBox == object) {
				if (side != CollisionSide::left || this->direction != MoveDirection::RightToLeft) {
					this->smashLeft = false;
				}
				else {
					this->SetVx(0);
					// push thêm vài pixel để đẩy nhân vật rơi xuống
					if (this->GetOnAirState() == OnAir::None) {
						this->pos.x += 4;
					}
				}
				if (side != CollisionSide::right || this->direction != MoveDirection::LeftToRight) {
					this->smashRight = false;
				}
				else {
					this->SetVx(0);
					// push thêm vài pixel để đẩy nhân vật rơi xuống
					if (this->GetOnAirState() == OnAir::None) {
						this->pos.x -= 4;
					}
				}
				if (side == CollisionSide::bottom && !this->StandOnCurrentGround()) {
					this->TryStandOnGround(object);
				}
			}
			else {
				collisionOut colOut;
				colOut.side = side;
				OnCollisionWithSolidBox(object, &colOut);
				/*if ((side == CollisionSide::left && this->vx < 0) || (side == CollisionSide::right && this->vx > 0)) {
					
				}
				if (side == CollisionSide::bottom && !this->StandOnCurrentGround()) {
					this->TryStandOnGround(object);
				}*/
			}
			return false;
		}
		case Type::ENEMY: {
			auto enemyCast = (Enemy*)object;
			// ở trạng thái không thể tấn công
			if (this->IsImmortal() || this->IsNonAttackable())
				return false;
			// ở trạng thái DASHING
			if (this->state == State::DASHING)
				return false;
			// ở trạng thái shield down và chạm là bottom
			if (this->state == State::SHIELD_DOWN && side == CollisionSide::bottom)
				return false;
			// enemy gây sát thương kiểu shock điện
			if (enemyCast->GetDamageEffect() == Enemy::DamageEffect::Eletric) {
				this->OnShockedElectric(enemyCast);
			}
			else {
				this->OnCollisionWithEnemy(object);
			}
			return true;
		}
		case Type::ROPE: {
			//if (this->GetOnAirState() == Player::OnAir::Falling) {
			//	PlayerHandOnRope* handOnRope = new PlayerHandOnRope();
			//	SceneManager::getInstance()->AddObjectToCurrentScene(handOnRope);
			//}
		}
	}
	if (object->tag == Tag::ITEM) {
		this->LootItem((Item*)object);
		return true;
	}
	return false;
}
void Player::OnFallingOffGround() {
 	if (this->GetOnAirState() == Player::OnAir::None) {
		if (this->IsFootStepOn() && this->GetStandingGround()->pos.y == 44)
			this->SetOnAirState(Player::OnAir::DropToWater);
		else
			this->SetOnAirState(Player::OnAir::Falling);
		this->ChangeState(State::JUMPING);
		this->vy -= 0.9;
		this->SetStandingGround(NULL);
		this->isGroundVelocityApplied = false;
	} 
}
bool Player::TryStandOnGround(Object* ground) {
	if (ground->type != Type::GROUND && ground->type != Type::SOLIDBOX && ground->type != Type::PLATFORM)
		return FALSE;

	auto groundBox = ground->getStaticObjectBoundingBox();
	auto playerBox = this->getBoundingBox();
	auto onAir = this->GetOnAirState();
	if (onAir == OnAir::Jumping || onAir == OnAir::Falling || onAir == OnAir::JumpFromWater) {
		float dentaY = groundBox.top - playerBox.bottom;
		if (dentaY > 0 && dentaY <= 10) {
			this->OnStandingOnGround(ground);
			return TRUE;
		}
	}
	return FALSE;
}
void Player::OnSmashSolidBox(Object* object, CollisionSide side) {
	/*KeyboardManager *keyboard = KeyboardManager::getInstance();
	if ((side == CollisionSide::left && vx < 0) || (side == CollisionSide::right && vx > 0))
		this->SetVx(0);
	this->collidedSolidBox = object;
	auto bound = object->getStaticObjectBoundingBox();
	switch (side) {
	case CollisionSide::left: {
		this->pos.x = bound.right + this->getWidth() / 2 - 4;

		this->smashLeft = true;
		this->smashRight = false;
		break;
	}
	case CollisionSide::right: {
		this->pos.x = bound.left - this->getWidth() / 2 + 4;
		this->smashRight = true;
		this->smashLeft = false;
	}
	}*/
	KeyboardManager *keyboard = KeyboardManager::getInstance();
	if ((side == CollisionSide::left && vx < 0) || (side == CollisionSide::right && vx > 0))
		this->SetVx(0);
	this->collidedSolidBox = object;
	if (this->GetOnAirState() == OnAir::Jumping) {
		this->vy = 0;
		this->SetOnAirState(OnAir::Falling);
	}
	auto bound = object->getStaticObjectBoundingBox();
	switch (side) {
	case CollisionSide::left: {
		//this->pos.x = bound.right + this->getWidth() / 2 - 4;
		if (keyboard->isKeyDown(PLAYER_MOVE_LEFT) && this->onAirState != OnAir::None)
			this->pos.x = bound.right + this->getWidth() / 2;
		else
		{
			if (this->onAirState == OnAir::None)
				this->pos.x = bound.right + this->getWidth() / 2 + 4;
			else
			{
				this->pos.x = bound.right + this->getWidth() / 2 + 2;
			}
		}

		this->smashLeft = true;
		this->smashRight = false;
		break;
	}
	case CollisionSide::right: {
		//this->pos.x = bound.left - this->getWidth() / 2 + 4;
		if (keyboard->isKeyDown(PLAYER_MOVE_RIGHT) && this->onAirState != OnAir::None)
			this->pos.x = bound.left - this->getWidth() / 2;
		else
		{
			if (this->onAirState == OnAir::None)
				this->pos.x = bound.left - this->getWidth() / 2 - 4;
			else
			{
				this->pos.x = bound.left - this->getWidth() / 2 - 2;
			}
		}
		this->smashRight = true;
		this->smashLeft = false;
	}
	}
}
void Player::OnHeadOnSolidBox(Object* solid) {
	this->SetVy(0);
}
void Player::OnClimbingTheRope(Object* rope) {
	this->ChangeState(State::CLIMBING);
	this->pos.y = rope->getBoundingBox().top - this->getHeight() / 2 - 2;
}
bool Player::AcceptNoCollision(Object* object, CollisionSide side) {
	auto objBox = object->getStaticObjectBoundingBox();
	auto playerBox = this->getBoundingBox();

	if (side == CollisionSide::top || side == CollisionSide::bottom)
		return false;
	if (side == CollisionSide::right) {
		float dentaX = playerBox.right - objBox.left;
		float dentaY = playerBox.bottom - objBox.top;
	}
	if (this->GetOnAirState() == OnAir::Jumping) {
		if (this->GetPreviousState()->state == State::FLOATING) {
			this->SetOnAirState(OnAir::DropToWater);
		}
		else {
			this->SetOnAirState(OnAir::Falling);
		}
	}
}
void Player::OnCollisionWithEnemy(Object* enemy) {
	if (this->GetMoveDirection() == MoveDirection::LeftToRight) {
		this->pos.x -= 5;
	}
	else {
		this->pos.x += 5;
	}
	if (this->GetOnAirState() == OnAir::None) {
		this->ChangeState(State::BEATEN);
	}
	else {
		this->ChangeState(State::FLYING_BEATEN);
	}
	// sát thương khi va chạm enemy luôn là 1
	this->BeingAttacked(1);
}
void Player::OnCollisionWithBullet(Bullet* bullet) {
	if (this->GetMoveDirection() == MoveDirection::LeftToRight) {
		this->pos.x -= 5;
	}
	else {
		this->pos.x += 5;
	}
	this->SetVx(0);
	if (this->GetOnAirState() == OnAir::None) {
		this->ChangeState(State::BEATEN);
	}
	else {
		this->ChangeState(State::FLYING_BEATEN);
	}
	this->BeingAttacked(bullet->GetBulletDamage());
}
void Player::OnShockedElectric(Object* object) {
	if (this->GetMoveDirection() == MoveDirection::LeftToRight) {
		this->pos.x -= 5;
	}
	else {
		this->pos.x += 5;
	}
	this->SetVx(0);
	this->ChangeState(State::SHOCKING);
	this->BeingAttacked(object->GetCollisionDamage());
}
void Player::OnShieldFloatOnWater(Object* object) {
	this->SetOnAirState(Object::OnAir::FloatAboveWater);
	this->pos.y = object->getBoundingBox().top + this->getHeight() / 2 + 8;
}
void Player::OnBeingCarried(Object* object) {
	//this->carriedObj = object;
}
#pragma endregion


