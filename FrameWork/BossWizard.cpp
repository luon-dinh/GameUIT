#include"BossWizard.h"
#include"Camera.h"
#include"SceneManager.h"

BossWizard* BossWizard::instance = NULL;

BossWizard::BossWizard()
{
	LoadAllAnimations();
	LoadAllStates();
	this->pos.x = 200;
	this->pos.y = 120;
	this->vx = 0;
	this->vy = 0;
	this->health = 20;
	this->deltaX = this->deltaY = 0;
	this->hitTime = 0;
	this->isCollide = false;
	this->direction = Object::MoveDirection::LeftToRight;
	this->flyMode = 1;
	this->canShootOnAir = false;
	this->timeDelayShootOnAir = 0;
	this->tag = Tag::BOSSWIZARD;
	this->type = Type::WIZARD;
	this->timeToShoot = 1080;
	this->delayShoot = 0;
	this->timeNotRender = 0;
	this->wizardState = wizardStates[State::FLYING];
	this->currentanimation = animations[State::FLYING];
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
	auto sprite = currentanimation->getSprite(currentanimation->curframeindex);
	RECT rect = sprite->getRECT();
	return((rect.top + rect.bottom) / 2 - rect.bottom);
}

float BossWizard::getPosToRight()
{
	auto sprite = currentanimation->getSprite(currentanimation->curframeindex);
	RECT rect = sprite->getRECT();
	return(rect.right-(rect.right + rect.left) / 2);
}

float BossWizard::getWidth()
{
	return width;
}

BoundingBox BossWizard::getBoundingBox()
{
	auto sprite = currentanimation->getSprite(currentanimation->curframeindex);
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
	if (state == State::DEAD)
	{
		if (this->currentanimation->curframeindex = this->currentanimation->curframeindex - 1 && this->timeNotRender > 900)
			DeactivateObjectInGrid();
		if (this->onAirState != OnAir::None&&this->state != State::FLYING)
			this->currentAnimation->Update(dt);
	}
	auto player = Player::getInstance();
	if (this->state != State::FLYING&&state!=State::DEAD)
		this->currentanimation->Update(dt);
	//bay vào đầu hoặc cuối map
	if (this->pos.x < minMap || this->pos.x > maxMap)
	{
		if (this->pos.x < minMap&&this->direction == MoveDirection::RightToLeft)
		{
			if (this->onAirState == OnAir::None&&this->state == State::FLYING)
				this->onAirState = OnAir::Falling;
			this->vx = 0;
		}
		if (this->pos.x > maxMap&&this->direction == MoveDirection::LeftToRight)
		{
			if (this->onAirState == OnAir::None&&this->state == State::FLYING)
				this->onAirState = OnAir::Falling;
			this->vx = 0;
		}
	}
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	if (isCollide)
	{
		timeNotRender += dt;
	}
	//bị bắn 2 phát thì bay
	if (hitTime >= 2 && this->onAirState == OnAir::None)
	{
		flyTimes = rand() % 3 + 1;
		flyMode = rand() % 3 + 2;
		ChangeState(State::FLYING);
		flyTimes--;
		hitTime = 0;
		return;
	}
	this->wizardState->Update(dt);
	//player đang đứng trên thanh ground thì cười
	if (player->GetStandingGround() != NULL && player->GetStandingGround()->type == Type::GROUND &&this->onAirState == OnAir::None&&this->state!=State::FLYING)
	{
		this->vx = 0;
		this->ChangeState(State::STAND_SMILE);
		return;
	}
	
	
}

void BossWizard::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, pos.y, 0));
	
	if (this->timeNotRender == 0)
	{
		if (this->direction == Player::MoveDirection::LeftToRight) {
			// move from left to right
			currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal);
		}
		else {
			currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
		}
	}
	else
	{
		if ((int)timeNotRender % 2 == 0)
		{
			if (this->direction == Player::MoveDirection::LeftToRight) {
				// move from left to right
				currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal);
			}
			else {
				currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y));
			}
		}
		if (timeNotRender > 1000)
		{
			timeNotRender = 0;
			isCollide = false;
		}
	}
}


void BossWizard::OnCollision(Object* object, collisionOut* colOut)
{
	switch (object->type)
	{
	case Type::SOLIDBOX:
	case Type::GROUND:
		deltaX = deltaY = 0;
		if(colOut->side==CollisionSide::bottom)
		{
			this->vy = 0;
			this->vx = 0;
			this->pos.y = object->getBoundingBox().top + this->getHeight() / 2;
			if (this->direction == MoveDirection::LeftToRight)
				this->direction = MoveDirection::RightToLeft;
			else
			{
				this->direction = MoveDirection::LeftToRight;
			}
			// nếu bay gần thì đấm rồi cuyển state khác
			if (this->flyMode == 1)
			{
				ChangeState(State::STAND_PUNCH);
			}
			//bay xa thì chuyển state shoot
			else
			{
				ChangeState(State::ATTACK);
			}
		}
		break;
	default:
		break;
	}
	if (object->tag == Tag::SHIELD)
	{
		auto shield = Shield::getInstance();
		if (shield->state == Shield::ShieldState::Attack)
		{
			//render khong render
			//this->currentanimation = animations[State::DEAD];
			this->health--;
			if (this->health <= 0)
			{
				//isDead = true;
				ChangeState(State::DEAD);
			}
			if (health == 10)
				this->turnOffLight = true;
			this->hitTime++;
			this->isCollide = true;
			return;
		}
	}
	if (object->tag == Tag::PLAYER)
	{
		this->isCollide = true;
		return;
	}
}

void BossWizard::OnNotCollision(Object* object)
{
	
}

bool BossWizard::OnRectCollided(Object* object, CollisionSide side)
{
	if (object->type == Type::GROUND&&side==CollisionSide::bottom&&this->turnOffLight)
	{
		this->direction = BossWizard::MoveDirection::LeftToRight;
		this->vy = 0;
		ChangeState(State::STAND_PUNCH);
	}
	if (object->type == Type::ONOFF&&this->state==State::STAND_PUNCH&& this->turnOffLight)
	{
		// đổi map 
		SceneManager::getInstance()->TurnOnOffLight();
		this->turnOffLight = false;
	}
	return true;
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
	currentanimation = animations[stateName];
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
		this->vy = flySpeedy;
		this->deltaX = this->deltaY = 0;
		this->onAirState = OnAir::Jumping;
		break;
	case State::ATTACK:
		this->vy = 0;
		this->vx = 0;
		this->timeToShoot = 1080;
		this->delayShoot = 0;
		this->onAirState = OnAir::None;
		break;
	case State::STAND_PUNCH:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::STAND_SMILE:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::RUNNING:
		this->vy = 0;
		this->onAirState = OnAir::None;
		break;
	case State::DEAD:
		this->onAirState = OnAir::None;
		this->vx = this->vy = 0;
		break;
	default:
		break;
	}
	currentanimation->curframeindex = 0;
	this->deltaX = this->deltaY = 0;
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
	wizardStates[State::DEAD] = new BossWizardDeadState();
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