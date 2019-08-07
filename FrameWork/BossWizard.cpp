#include"BossWizard.h"
#include"Camera.h"
#include"SceneManager.h"

BossWizard* BossWizard::instance = NULL;

BossWizard::BossWizard()
{
	LoadAllAnimations();
	LoadAllStates();
	this->pos.x = 200;
	this->pos.y = 200;
	this->vx = 0;
	this->vy = 0;
	this->health = maxHelth;
	this->deltaX = this->deltaY = 0;
	this->hitTime = 0;
	this->countBullet = 0;
	this->isCollide = false;
	this->direction = Object::MoveDirection::LeftToRight;
	this->flyMode = 0;
	this->isMode1 = false;
	this->canShootOnAir = false;
	this->tag = Tag::BOSSWIZARD;
	this->type = Type::ENEMY;
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
	auto sprite = currentanimation->getSprite(currentanimation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	height = rect.top - rect.bottom;
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
	auto sprite = currentanimation->getSprite(currentanimation->curframeindex);
	RECT rect = sprite->getRECT();
	width = rect.right - rect.left;
	height = rect.top - rect.bottom;
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

	//nửa máu thì có thể tắt đèn
	if (health <= 10)
		this->turnOffLight = true;
	else
	{
		this->turnOffLight = false;
	}
	auto player = Player::getInstance();
	this->currentanimation->Update(dt);

	//bay vào đầu hoặc cuối map

	if (this->state != State::FLYING)
		canNewParapol = true;
	this->wizardState->Update(dt);

	if (this->state == State::FLYING&&this->flyMode == 1&& canNewParapol)
	{

		D3DXVECTOR2 pos2;
		pos2.y = this->pos.y + this->maxFlyy1;
		if (this->direction == BossWizard::MoveDirection::LeftToRight)
		{
			this->vx = this->flySpeedx1;
			pos2.x = this->pos.x + (this->maxXToFly1 - 10) / 2;

		}
		else
		{
			this->vx = -this->flySpeedx1;
			pos2.x = this->pos.x - (this->maxXToFly1 - 10) / 2;
		}
		this->parapol = new Equation(this->pos, pos2);

		canNewParapol = false;
	}

	if (flyMode==1 && this->state == State::FLYING)
	{
		this->vy = (this->parapol->GetYFromX(this->pos.x + this->vx) - this->parapol->GetYFromX(this->pos.x));
		if (vy < -3)
			this->vx *= 0.9;
		this->pos.x += this->vx;
		
		this->pos.y = this->parapol->GetYFromX(this->pos.x);
	}
	else
	{
		this->pos.x += this->vx;
		this->pos.y += this->vy;
	}

	
	if (!isCollidable||this->health < 10)
	{
		timeNotRender += dt;
	}

	//bị bắn 2 phát thì bay

	//player đang đứng trên thanh ground thì cười
	if (player->GetStandingGround() != NULL && player->GetStandingGround()->type == Type::GROUND &&this->GetStandingGround()!=NULL&&this->GetStandingGround()->type==Type::SOLIDBOX)
	{
		this->vx = 0;
		this->ChangeState(State::STAND_SMILE);
		return;
	}
	
	
}

void BossWizard::Render()
{
	D3DXVECTOR3 vectortoDraw = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, pos.y, 0));
	
	D3DCOLOR color;
	if (SceneManager::getInstance()->IsLightOn()==true)
	{
		color = D3DCOLOR_XRGB(255, 255, 255);
	}
	else
	{
		color = D3DCOLOR_XRGB(0, 0, 0);
		//return;
	}

	if (this->timeNotRender > 0||this->health < 10)
	{
		if ((int)timeNotRender % 2 == 0)
		{
			if (this->direction == Player::MoveDirection::LeftToRight) {
				// move from left to right
				currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal, color);
			}
			else {
				currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), color);
			}
		}
		if (timeNotRender > maxTimeNotRender)
		{
			timeNotRender = 0;
			isCollidable = true;
		}
		
	}
	else
	{
		if (this->direction == Player::MoveDirection::LeftToRight) {
			// move from left to right
			currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), TransformationMode::FlipHorizontal, color);
		}
		else {
			currentanimation->Render(D3DXVECTOR2(vectortoDraw.x, vectortoDraw.y), color);
		}
	}
}


void BossWizard::OnCollision(Object* object, collisionOut* colOut)
{
	auto player = Player::getInstance();
	this->SetStandingGround(object);
	switch (object->type)
	{
	case Type::SOLIDBOX:
		if(colOut->side==CollisionSide::bottom)
		{
			deltaX = deltaY = 0;
			this->vy = 0;
			this->vx = 0;
			if (this->flyMode == 1)
				this->isMode1 = true;
			if (this->state == State::BEATEN&&this->health <= 0)
				ChangeState(State::DEAD);
			else
			{
				ChangeState(State::STANDING);
			}
			this->pos.y = object->getBoundingBox().top + this->getHeight() / 2 - 4;
		}
		break;
	case Type::GROUND:
		if (colOut->side == CollisionSide::bottom)
		{
			deltaX = deltaY = 0;
			this->direction = BossWizard::MoveDirection::LeftToRight;
			this->vy = 0;
			this->vx = 0;
			if (this->state == State::BEATEN&&this->health <= 0)
				ChangeState(State::DEAD);
			else
			{
				ChangeState(State::STANDING);
			}
			this->pos.y = object->getBoundingBox().top + this->getHeight() / 2 - 4;
		}
		break;
	default:
		break;
	}
	
}

void BossWizard::OnNotCollision(Object* object)
{
	/*if (this->state != State::FLYING)
		this->vy -= 0.3;*/
}

bool BossWizard::OnRectCollided(Object* object, CollisionSide side)
{
	/*if (object->type == Type::GROUND || object->type == Type::SOLIDBOX&& side==CollisionSide::bottom)
	{
		this->vy = 0;
	}*/
	if (object->type == Type::ONOFF&&this->state==State::STAND_PUNCH&& this->turnOffLight&&SceneManager::getInstance()->IsLightOn())
	{
		// đổi map 
		SceneManager::getInstance()->TurnOnOffLight();
		this->flyMode = 1;
		ChangeState(State::FLYING);
		this->turnOffLight = false;
	}
	if (object->tag == Tag::SHIELD)
	{
		auto shield = Shield::getInstance();
		if (shield->state == Shield::ShieldState::Attack)
		{
			//render khong render
			//this->currentanimation = animations[State::DEAD];
			this->health -= shield->GetCollisionDamage();
			this->isCollidable = false;
			if (this->health <= 0&&this->onAirState==OnAir::None&&this->state!=State::FLYING)
			{
				//isDead = true;
				ChangeState(State::DEAD);
			}
			else if (this->state == State::FLYING && this->deltaY>4 && this->onAirState != OnAir::None)
			{
				ChangeState(State::BEATEN);
			}
			this->hitTime++;
			if (this->hitTime >= 2)
			{
				this->flyTimes = rand() % 3 + 1;
			}
			return false;
		}
	}
	if (object->tag == Tag::PLAYER)
	{
		this->health -= Player::getInstance()->GetDamage();
		this->isCollidable = false;
		if (this->health <= 0 && this->onAirState == OnAir::None&&this->state != State::FLYING)
		{
			//isDead = true;
			ChangeState(State::DEAD);
		}
		else if(this->state == State::FLYING && this->deltaY > 4)
		{
			ChangeState(State::BEATEN);
		}
		this->hitTime++;
		if (this->hitTime >= 2)
		{
			this->flyTimes = rand() % 3 + 1;
		}
		return true;
	}
	if (object->tag == Tag::PLAYER_PART)
	{
		this->health -= object->GetCollisionDamage();
		this->isCollidable = false;
		if (this->health <= 0 && this->onAirState == OnAir::None&&this->state != State::FLYING)
		{
			//isDead = true;
			ChangeState(State::DEAD);
		}
		else if (this->state == State::FLYING && this->deltaY > 4)
		{
			ChangeState(State::BEATEN);
		}
		this->hitTime++;
	}
	return false;
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
	this->state = stateName;
	this->wizardState = wizardStates[stateName];
	currentanimation = animations[stateName];
	float posy2 = this->getPosToBottom();
	this->pos.y =this->pos.y+ (posy2 - posy1);
	switch (stateName)
	{
	case State::STANDING:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::FLYING:
		SoundManager::getinstance()->play(SoundManager::wizard_flying);
		this->canShootOnAir = true;
		this->vy = flySpeedy;
		this->deltaX = this->deltaY = 0;
		this->onAirState = OnAir::Jumping;
		break;
	case State::ATTACK:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::STAND_PUNCH:
		this->vy = 0;
		this->vx = 0;
		this->onAirState = OnAir::None;
		break;
	case State::STAND_SMILE:
		SoundManager::getinstance()->stop(SoundManager::SoundName::wizard_lazer);
		SoundManager::getinstance()->stop(SoundManager::SoundName::wizard_fire);
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
		this->isCollidable = false;
		break;
	case State::BEATEN:
		this->onAirState = OnAir::Falling;
		this->vx = 0;
		this->vy = -this->flySpeedy;
		break;
	default:
		break;
	}
	this->deltaX = this->deltaY = 0;
}

void BossWizard::LoadAllAnimations()
{
	animations[State::STANDING] = new Animation(Tag::BOSSWIZARD, 0, 1);
	animations[State::STAND_SMILE] = new Animation(Tag::BOSSWIZARD, 0, 3, 120/3);
	animations[State::RUNNING] = new Animation(Tag::BOSSWIZARD, 3, 7);
	animations[State::DEAD] = new Animation(Tag::BOSSWIZARD, 8, 10);
	animations[State::ATTACK] = new Animation(Tag::BOSSWIZARD, 10, 13, 800/3);
	animations[State::FLYING] = new Animation(Tag::BOSSWIZARD, 13, 16);
	animations[State::STAND_PUNCH] = new Animation(Tag::BOSSWIZARD, 16, 18);
	animations[State::BEATEN] = new Animation(Tag::BOSSWIZARD, 7, 8);
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
	wizardStates[State::BEATEN] = new BossWizardBeatenState();
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