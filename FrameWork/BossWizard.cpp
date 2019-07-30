#include"BossWizard.h"
#include"Camera.h"

BossWizard* BossWizard::instance = NULL;

BossWizard::BossWizard()
{
	LoadAllAnimations();
	LoadAllStates();
	this->pos.x = 1500;
	this->pos.y = 80;
	this->vx = 0;
	this->vy = 0;
	this->direction = Object::MoveDirection::LeftToRight;
	ChangeState(State::FLYING);
	this->onAirState = OnAir::Falling;
}

BossWizard::~BossWizard()
{

}

float BossWizard::getHeight()
{
	return height;
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
	if (this->state != State::FLYING)
		this->curanimation->Update(dt);
	this->wizardState->Update(dt);
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	
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
			ChangeState(State::STANDING);
		}
		deltaX = deltaY = 0;
		break;
	case Type::WATERRL:
		this->pos.y = 66;
		this->vy = 0;
		ChangeState(State::STANDING);
		deltaX = deltaY = 0;
		break;
	default:
		break;
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
	this->state = stateName;
	this->wizardState = wizardStates[stateName];
	curanimation = animations[stateName];
	switch (stateName)
	{
	case State::STANDING:
		this->vy = 0;
		this->onAirState = OnAir::None;
		break;
	case State::FLYING:
		this->vy = 2;
		this->onAirState = OnAir::Jumping;
		break;
	case State::ATTACK:
		break;
	case State::STAND_PUNCH:
		this->onAirState = OnAir::None;
		break;
	case State::STAND_SMILE:
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

}

void BossWizard::LoadAllAnimations()
{
	animations[State::STANDING] = new Animation(Tag::BOSSWIZARD, 0, 1);
	animations[State::STAND_SMILE] = new Animation(Tag::BOSSWIZARD, 0, 3);
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