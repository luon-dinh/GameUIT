#include"Player.h"
#include"Camera.h"
#include"Debug.h"

Player* Player::instance = NULL;

Player::Player()
{
	LoadAllAnimations();
	LoadAllStates();

	this->pos.x = 30;
	this->pos.y = 80;
	this->tag = Tag::PLAYER;
	this->type = Type::NONE;
	this->health = 100;
	this->energy = 0;
	this->vx = 0;
	this->vy = 0;
	this->direction = MoveDirection::LeftToRight;

	this->state = State::JUMPING;
	this->playerstate = playerStates[State::JUMPING];
	this->curanimation = animations[this->state];
	this->prevState = NULL;
	this->collisionAffect = TRUE;

	this->groundCollision = new GroundCollision();
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
	animations[JUMPING] = new Animation(PLAYER, 7, 8);
	animations[DUCKING]	= new Animation(PLAYER, 6, 7);
	animations[DUCKING_PUNCHING] = new Animation(PLAYER, 15, 17);
	animations[SHIELD_UP] = new Animation(PLAYER, 5, 6);
	animations[ROLLING] = new Animation(PLAYER, 8, 10);
	animations[KICKING] = new Animation(PLAYER, 10, 11);
	animations[DASHING] = new Animation(PLAYER, 17, 19);
	animations[FLOATING] = new Animation(PLAYER, 32, 40);
	animations[DIVING] = new Animation(PLAYER, 40, 46);
	animations[SHIELD_DOWN] = new Animation(PLAYER, 19, 20);
	animations[SHIELD_ATTACK] = new Animation(PLAYER, 11, 13);
	animations[STAND_PUNCH] = new Animation(PLAYER, 13, 15);
}

void Player::LoadAllStates() {
	this->playerStates[State::STANDING] = new PlayerStandingState();
	this->playerStates[State::RUNNING]  = new PlayerRunningState();
	this->playerStates[State::JUMPING]  = new PlayerJumpingState();
	this->playerStates[State::DUCKING]  = new PlayerSittingState();
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
}




Player::~Player()
{

}


BoundingBox Player::getBoundingBox()
{
	return this->playerstate->getBoundingBox();
}

void Player::Update(float dt)
{
	// Update state
	this->playerstate->Update(dt);
	// Nếu state không đổi thì update vị trí
	if (!this->isStateChanged) {
		this->UpdatePosition();
	}
	else {
		this->isStateChanged = false;
	}
	// Update animation
	this->curanimation->Update(dt);
}

void Player::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x,pos.y,0));
	if (this->direction == Player::MoveDirection::LeftToRight) {
		// move from left to right
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y),TransformationMode::FlipHorizontal);
	}
	else {
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
	}
	if (this->state == State::FLOATING) {
		int a = 1;
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

void Player::ChangeState(State stateName) {
	if (this->state == stateName)
		return;

	OnStateChanged(this->state, stateName);

	InnerChangeState(stateName);
	auto shield = Shield::getInstance();


	// thay đổi riêng biệt cho từng loại state
	switch (stateName) {
		case State::STANDING: {
			if (this->hasShield) {
				shield->SetShieldState(Shield::ShieldState::Defense);
			}
			this->SetAirState(Player::OnAir::None);
			this->SetVx(0);
			break;
		}
		case State::RUNNING:{
			this->SetAirState(Player::OnAir::None);
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
			if (this->prevState->state == State::FLOATING) {
				shield->SetShieldState(Shield::ShieldState::Transparent);
				this->SetAirState(OnAir::JumpFromWater);
				return;
			}
			this->SetAirState(OnAir::Jumping);
			break;
		}
		case State::DASHING:{
			// dash khi có shield thì shield k render, ngược lại nghĩa là shield đang ở trạng thái attack
			if (this->hasShield)
				shield->SetShieldState(Shield::ShieldState::NotRender);
			if (this->direction == MoveDirection::LeftToRight) {
				SetVx(PLAYER_DASH_SPEED);
			}
			else {
				SetVx(-PLAYER_DASH_SPEED);
			}
			break;
		}
		case State::DIVING: {
			if (this->hasShield) {
				shield->SetShieldState(Shield::ShieldState::NotRender);
			}
			break;
		}
		case State::FLOATING: {
			if (this->hasShield) {
				shield->SetShieldState(Shield::ShieldState::NotRender);
			}
			this->SetAirState(OnAir::None);
			this->vx = -WATER_SPEED;
			break;
		}
		case State::ROLLING:{
			if (this->hasShield) {
				shield->SetShieldState(Shield::ShieldState::NotRender);
			}
			
			break;
		}
		case State::KICKING: {
			if (this->hasShield) {
				shield->SetShieldState(Shield::ShieldState::Transparent);
				if (this->direction == MoveDirection::LeftToRight) {
					shield->SetShieldDirection(FALSE, Shield::ShieldDirection::RightToLeft);
				}
				else {
					shield->SetShieldDirection(FALSE, Shield::ShieldDirection::LeftToRight);
				}
			}

			break;
		}
		case State::SHIELD_DOWN: {
			shield->SetShieldState(Shield::ShieldState::Defense);
			break;
		}
		case State::SHIELD_ATTACK: {
			SetVx(0);
			Shield::getInstance()->SetShieldState(Shield::ShieldState::Transparent);
			break;
		}
		case State::STAND_PUNCH: {
			SetVx(0);
			break;
		}
	}
}

BOOL Player::IsOnMainGround() {
	if (!this->groundCollision || !this->groundCollision->GetGround())
		return FALSE;

	// tung độ của main ground là 44
	return this->groundCollision->GetGround()->pos.y == 44;
}

BOOL Player::IsReachMaxJump() {
	return this->vy <= 0 && this->onAirState == OnAir::Jumping;
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
	this->vx = vx;
	if (vx == 0)
		return;
	if (this->direction == MoveDirection::LeftToRight) {
  		if (vx < 0) {
   			this->direction = MoveDirection::RightToLeft;
		}
	}
	else {
		if (vx > 0) {
			this->direction = MoveDirection::LeftToRight;
		}
	}
	Shield::getInstance()->SetShieldDirection(TRUE);
}


void Player::SetVx(float vx, BOOL changePlayerDirection) {
	if (changePlayerDirection) {
		SetVx(vx);
		return;
	}
	this->vx = vx;
}

void Player::SetVy(float vy) {
	this->vy = vy;
	if (this->vy <= 0) {
		// Nếu vận tốc <= 0 khi đang ở trạng thái nhảy thì rơi xuống lại
		if (this->onAirState == OnAir::Jumping || this->onAirState == OnAir::JumpFromWater)
			SetAirState(OnAir::Falling);
	}
}


void Player::SetVelocity(D3DXVECTOR2 veloc) {
	this->vx = veloc.x;
	this->vy = veloc.y;
}

void Player::AddPosX() {
	if (this->IsStopBySolidBox())
		return;
	this->vx += this->accelerate.x;
	this->pos.x += this->vx;
}

void Player::AddPosY() {
	if (this->vy <= -5)
		this->accelerate.y = 0;
	this->SetVy(this->vy + this->accelerate.y);
	this->pos.y += this->vy;
}

void Player::UpdatePosition() {
	this->accelerate.x = 0;
	AddPosX();
	AddPosY();
}

void Player::SetMoveDirection(MoveDirection moveDir) {
	auto curMoveDir = this->direction;
	this->direction = moveDir;
	if (this->direction != curMoveDir) {
		this->vx *= -1;
	}
	if (!this->hasShield) {
		return;
	}
	auto shield = Shield::getInstance();
	if (this->direction == MoveDirection::LeftToRight) {
		shield->direction = Shield::ShieldDirection::LeftToRight;
	}
	else {
		shield->direction = Shield::ShieldDirection::RightToLeft;
	}
}

void Player::SetAccelerate(D3DXVECTOR2 accelerate) {
	this->accelerate.x = accelerate.x;
	this->accelerate.y = accelerate.y;
}

BOOL Player::GetCollisionAffect() {
	return this->collisionAffect;
}

void Player::SetCollisionAffect(BOOL value) {
	this->collisionAffect = value;
}

void Player::SetGroundCollision(GroundCollision* groundCollision) {
	if (this->groundCollision != groundCollision) {
		delete this->groundCollision;
		this->groundCollision = groundCollision;
	}
}

GroundCollision* Player::GetGroundCollision() {
	return this->groundCollision;
}

Player::OnAir Player::GetOnAirState() {
	return this->onAirState;
}

Player::OnAir Player::GetPreOnAirState() {
	return this->preOnAir;
}
void Player::SetAirState(OnAir onAirState) {
	if (this->onAirState == onAirState)
		return;
	auto oldState = this->onAirState;
	this->preOnAir = oldState;
	this->onAirState = onAirState;

	switch (this->onAirState) {
		case OnAir::None:{
			this->accelerate.y = 0;
			this->vy = 0;
			return;
		}
		case OnAir::Jumping: {
			this->accelerate.y = -GROUND_GRAVITY;
			this->vy = PLAYER_JUMP_SPEED;
			return;
		}
		case OnAir::DropToWater: {
			this->vy = -2;
			return;
		}
		case OnAir::Falling: {
			this->accelerate.y = -GROUND_GRAVITY;
			return;
		}
		case OnAir::JumpFromWater: {
			this->vy = 5;
			this->accelerate.y = -0.2;
			return;
		}
	}
}




int Player::getWidth()
{
	BoundingBox box = this->playerstate->getBoundingBox();
	return box.right - box.left;
}

int Player::getHeight()
{
	BoundingBox box = this->playerstate->getBoundingBox();
	return box.top - box.bottom;
}



#pragma region Collison Handler Implementation
void Player::OnCollision(Object* object, collisionOut* collisionOut) {
	// không xét va chạm với shield
	if (object->tag == Tag::SHIELD)
		return;
	this->playerstate->OnCollision(object, collisionOut);
}
void Player::OnNotCollision(Object* object) {
	if (!this->IsStopBySolidBox()) {
		this->smashLeft = this->smashRight = false;
	}
	switch (object->type) {
	case Type::GROUND: {
		// nếu đang ở trạng thái rơi xuống nước thì bỏ qua va chạm với ground
		if (this->GetOnAirState() == OnAir::DropToWater) {
			return;
		}
		// Trong trường hợp đã rơi khỏi ground hiện tại
		if (this->GetOnAirState() == OnAir::None) {
			if (this->StandOnCurrentGround() == FALSE && this->GetGroundCollision()->GetGround() != NULL) {
				this->OnFallingOffGround();
				return;
			}
		}
		break;
	}
	}
}
bool Player::OnRectCollided(Object* object) {
	switch (object->type) {
		case Type::GROUND:{
			// Nếu đang rơi xuống nước thì không xét va chạm với ground
			if (this->GetOnAirState() == OnAir::DropToWater)
				return true;
			if (this->GetOnAirState() == OnAir::Falling) {
				// nếu trạng thái trước đó là none thì bỏ qua xét va chạm rect với GROUND
				if (this->GetPreOnAirState() == OnAir::None)
					return true;
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
			return true;
		}	
		case Type::SOLIDBOX: {
			collisionOut colOut;
			bool isCollided = false;
			if (this->smashLeft) {
				colOut.side = CollisionSide::left;
				this->OnCollisionWithSolidBox(object, &colOut);
				isCollided = true;
			}
			if (this->smashRight) {
				colOut.side = CollisionSide::right;
				this->OnCollisionWithSolidBox(object, &colOut);
				isCollided = true;
			}
			bool tryStand = this->TryStandOnGround(object);
			if (isCollided)
				return true;
	 		return tryStand;
		}
	}
}

void Player::OnCollisionWithWater(Object* water, collisionOut* colOut) {
	this->ChangeState(State::FLOATING);
	auto objBox = water->getStaticObjectBoundingBox();
	this->pos.y = (objBox.top - objBox.bottom) / 2;
	this->SetGroundCollision(NULL);
}
void Player::OnFallingOffGround() {
	if (this->GetOnAirState() == Player::OnAir::None) {
		if (this->IsOnMainGround())
			this->SetAirState(Player::OnAir::DropToWater);
		else
			this->SetAirState(Player::OnAir::Falling);
		this->ChangeState(State::JUMPING);
		this->SetGroundCollision(NULL);
	}
}
void Player::OnStandingOnGround(Object* ground) {
	this->SetGroundCollision(new GroundCollision(ground, CollisionSide::bottom));
	this->ChangeState(State::STANDING);
	this->pos.y = ground->getBoundingBox().top - 4 + this->getHeight() / 2;
}
bool Player::StandOnCurrentGround() {
	auto ground = this->GetGroundCollision()->GetGround();

	if (ground == NULL)
		return FALSE;

	auto groundBox = ground->getStaticObjectBoundingBox();
	auto playerBox = this->getBoundingBox();

	if (Collision::getInstance()->IsCollide(playerBox, groundBox)) {
		return TRUE;
	}
	return FALSE;
}
bool Player::TryStandOnGround(Object* ground) {
	if (ground->type != Type::GROUND && ground->type != Type::SOLIDBOX)
		return FALSE;

	//if (this->GetGroundCollision()->GetGround() != NULL) {
	//	if (this->GetGroundCollision()->GetGround() == ground) {
	//		return FALSE;
	//	}
	//}

	auto groundBox = ground->getStaticObjectBoundingBox();
	auto playerBox = this->getBoundingBox();
	auto onAir = this->GetOnAirState();
	if (onAir == OnAir::Jumping || onAir == OnAir::Falling || onAir == OnAir::JumpFromWater) {
		float dentaY = groundBox.top - playerBox.bottom;
		if (dentaY > 0 && dentaY <= 5) {
			this->OnStandingOnGround(ground);
			return TRUE;
		}
	}
	return FALSE;
}
void Player::OnCollisionWithSolidBox(Object* solidBox, collisionOut* colOut) {
  	auto bound = solidBox->getStaticObjectBoundingBox();
	switch (colOut->side) {
		case CollisionSide::left:	OnSmashSolidBox(solidBox, CollisionSide::left); break;
		case CollisionSide::right:	OnSmashSolidBox(solidBox, CollisionSide::right);break;
		case CollisionSide::top: {
			this->SetVy(0);
			this->pos.y = bound.bottom - this->getHeight() / 2 - 2;
			this->smashLeft = this->smashRight = false;
			this->isStopBySolidBox = false;
			break;
		}
		case CollisionSide::bottom: {
			if (this->GetOnAirState() == OnAir::Falling) {
				OnStandingOnGround(solidBox);
			}
			this->smashLeft = this->smashRight = false;
			this->isStopBySolidBox = false;
			break;
		}
	}
}

bool Player::IsStopBySolidBox() {
	return (this->smashLeft && this->vx <= 0) || (this->smashRight &&  this->vx >= 0);
}

void Player::OnSmashSolidBox(Object* object, CollisionSide side) {
	if (this->GetOnAirState() == OnAir::Jumping){
		this->SetAirState(OnAir::Falling);
	}
	auto bound = object->getStaticObjectBoundingBox();
	switch (side) {
		case CollisionSide::top: {
			OnHeadOnSolidBox(object);
			return;
		}
		case CollisionSide::bottom: {
			return;
		}
		case CollisionSide::left: {
			this->pos.x = bound.right + this->getWidth() / 2;
			this->smashLeft = true;
			this->smashRight = false;
			break;
		}
		case CollisionSide::right: {
     			this->pos.x = bound.left - this->getWidth() / 2;
			this->smashRight = true;
			this->smashLeft = false;
		}
	}
}
void Player::OnHeadOnSolidBox(Object* solid) {
	this->SetVy(0);
}
void Player::OnStateChanged(State oldState, State newState) {
	this->isStateChanged = oldState != newState;
}
#pragma endregion


