#include"BossWizard.h"
#include"Camera.h"

BossWizard* BossWizard::instance = NULL;

BossWizard::BossWizard()
{
	LoadAllAnimations();
	LoadAllStates();
	this->pos.x = 200;
	this->pos.y = 120;
	this->vx = 0;
	this->vy = 0;
	this->direction = Object::MoveDirection::LeftToRight;
	this->flyMode = 3;
	this->wizardState = wizardStates[State::FLYING];
	this->curanimation = animations[State::FLYING];
	this->state = State::FLYING;
	this->onAirState = OnAir::Falling;
}

BossWizard::~BossWizard()
{

}

float BossWizard::getHeight()
{
	return height;
}

float BossWizard::getPosToBottom()
{
	auto sprite = curanimation->getSprite(curanimation->curframeindex);
	RECT rect = sprite->getRECT();
	return((rect.top + rect.bottom) / 2 - rect.bottom);
}

float BossWizard::getPosToRight()
{
	auto sprite = curanimation->getSprite(curanimation->curframeindex);
	RECT rect = sprite->getRECT();
	return(rect.right-(rect.right + rect.left) / 2);
}

float BossWizard::getWidth()
{
	return width;
}

BoundingBox BossWizard::getBoundingBox()
{
	auto sprite = curanimation->getSprite(curanimation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	height = rect.top - rect.bottom;
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	box.top = this->pos.y + height / 2;
	box.bottom = this->pos.y - height / 2;
	box.left = this->pos.x - width / 2;
	box.right = this->pos.x + width / 2;
	return box;

}

void BossWizard::Update(float dt)
{
	auto player = Player::getInstance();
	if(player->GetStandingGround() !=NULL&& player->GetStandingGround()->type==Type::GROUND &&this->onAirState==OnAir::None)
		this->ChangeState(State::STAND_SMILE);
	if (this->state != State::FLYING)
		this->curanimation->Update(dt);
	this->wizardState->Update(dt);
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	if (this->pos.x < 15&&state!=State::FLYING)
	{
		this->pos.x = 15;
		this->vx = 0;
		this->ChangeState(State::STANDING);
	}
	if (this->pos.x > 250&&state!=State::FLYING)
	{
		this->pos.x = 250;
		this->vx = 0;
		this->ChangeState(State::STANDING);
	}
}

void BossWizard::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, pos.y, 0));
	if (this->direction == Player::MoveDirection::LeftToRight) {
		// move from left to right
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal);
	}
	else {
		curanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
	}
}


void BossWizard::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->type)
	{
	case Type::SOLIDBOX:
	case Type::GROUND:
		if(colOut->side==CollisionSide::bottom)
		{
			this->vy = 0;
			this->pos.y = object->getBoundingBox().top + this->getHeight() / 2;
			if (this->direction == MoveDirection::LeftToRight)
				this->direction = MoveDirection::RightToLeft;
			else
			{
				this->direction = MoveDirection::LeftToRight;
			}
			ChangeState(State::RUNNING);
		}
		deltaX = deltaY = 0;
		break;
	default:
		break;
	}
	if (object->tag == Tag::SHIELD)
	{
		auto shield = Shield::getInstance();
		if (shield->state == Shield::ShieldState::Attack)
		{
			this->curanimation = animations[State::DEAD];
		}
	}
}

void BossWizard::OnNotCollision(Object* object)
{
	if (this->state != State::FLYING&&object->type == Type::GROUND)
	{
		if(Collision::getInstance()->IsCollide(this->getBoundingBox(),object->getBoundingBox()))
			this->vy = -2;
	}
}


void BossWizard::ChangeState(State stateName)
{
	if (stateName == this->state)
		return;
	auto player = Player::getInstance();
	float deltaX = this->pos.x - player->pos.x;
	if (deltaX > 0)
		this->direction = MoveDirection::RightToLeft;
	else
	{
		this->direction = MoveDirection::LeftToRight;
	}
	float posy1 = this->getPosToBottom();
	float posx1 = this->getPosToRight();
	this->state = stateName;
	this->wizardState = wizardStates[stateName];
	curanimation = animations[stateName];
	float posy2 = this->getPosToBottom();
	float posx2 = this->getPosToRight();
	this->pos.y =this->pos.y+ (posy2 - posy1);
	this->pos.x = this->pos.x + (posx2 - posx1);
	switch (stateName)
	{
	case State::STANDING:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::FLYING:
		this->vy = 2;
		this->onAirState = OnAir::Jumping;
		break;
	case State::ATTACK:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::STAND_PUNCH:
		this->onAirState = OnAir::None;
		break;
	case State::STAND_SMILE:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::RUNNING:
		this->vy = 0;
		if(this->direction==MoveDirection::LeftToRight)
			this->vx = 2;
		else
		{
			this->vx = -2;
		}
		this->onAirState = OnAir::None;
		break;
	default:
		break;
	}
	curanimation->curframeindex = 0;
}

void BossWizard::LoadAllAnimations()
{
	animations[State::STANDING] = new Animation(Tag::BOSSWIZARD, 0, 1);
	animations[State::STAND_SMILE] = new Animation(Tag::BOSSWIZARD, 0, 3, 120/3);
	animations[State::RUNNING] = new Animation(Tag::BOSSWIZARD, 3, 7);
	animations[State::FALLING] = new Animation(Tag::BOSSWIZARD, 7,8);
	animations[State::DEAD] = new Animation(Tag::BOSSWIZARD, 7, 10);
	animations[State::ATTACK] = new Animation(Tag::BOSSWIZARD, 10, 13);
	animations[State::FLYING] = new Animation(Tag::BOSSWIZARD, 13, 16);
	animations[State::STAND_PUNCH] = new Animation(Tag::BOSSWIZARD, 16, 18);
}

void BossWizard::LoadAllStates()
{
	wizardStates[State::STANDING] = new BossWizardStandingState();
	wizardStates[State::RUNNING] = new BossWizardRunningState();
	wizardStates[State::ATTACK] = new BossWizardShootingState();
	wizardStates[State::FLYING] = new BossWizardFlyingState();
	wizardStates[State::STAND_PUNCH] = new BossWizardPunchingState();
	wizardStates[State::STAND_SMILE] = new BossWizardStandSmileState();
}

void BossWizard::AddPosX()
{
	this->vx += this->accelerator.x;
	this->pos.x += this->vx;
}

void BossWizard::AddPosY()
{
	this->vy += this->accelerator.y;
	this->pos.y += this->vy;
}

BossWizard* BossWizard::getInstance()
{
	if (!instance)
		instance = new BossWizard();
	return instance;
}