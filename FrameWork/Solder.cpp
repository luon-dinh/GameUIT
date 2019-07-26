#include"Solder.h"
#include"Camera.h"

Solder::Solder(RunType runType)
{
	this->tag = Tag::BLUESOLDIER;
	LoadAllAnimation();
	timeCurrentState = 0;
	this->vy = 0;
	this->runType = runType;
	this->direction = Player::MoveDirection::RightToLeft;
	if (runType == RunType::SPECIAL)
		ChangeState(State::RUNNING);
	else
	{
		ChangeState(State::STANDING);
	}
}

Solder::~Solder() {

}

BoundingBox Solder::getBoundingBox()
{
	BoundingBox box;
	box.vx = this->vx;
	box.vy = this->vy;
	box.left = this->pos.x - 12;
	box.right = this->pos.x + 12;
	switch (this->stateName)
	{
	case State::RUNNING:
	case State::STANDING:
		box.top = this->pos.y + 22;
		box.bottom = this->pos.y - 21;
		return box;
	case State::DUCKING:
		box.top = this->pos.y + 6;
		box.bottom = this->pos.y - 21;
		return box;
	default:
		box.top = this->pos.y + 11;
		box.bottom = this->pos.y - 21;
		return box;
	}
}


void Solder::OnCollision(Object* object, collisionOut* colOut) {
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
		this->vy = 0;
		this->pos.y = object->getStaticObjectBoundingBox().top + this->getHeight() / 2;
		break;
	case Type::WATERRL:
		DeactivateObjectInGrid();
		break;
	default:
		break;
	}
}

bool Solder::OnRectCollided(Object* object, CollisionSide side)
{
	switch (object->type)
	{
	case Type::GROUND:
	case Type::SOLIDBOX:
		this->vy = 0;
		break;
	case Type::WATERRL:
		DeactivateObjectInGrid();
	default:
		break;
	}
	return true;
}

void Solder::OnNotCollision(Object* object)
{
	this->vy -= GROUND_GRAVITY;
}

void Solder::Update(float dt)
{

	if (!isDead)
	{
		if (runType == RunType::NOTRUN)
		{
			auto player = Player::getInstance();
			float deltax = this->pos.x - player->pos.x;
			if (deltax > 0)
				this->direction = Player::MoveDirection::RightToLeft;
			else
			{
				this->direction = Player::MoveDirection::LeftToRight;
			}
		}
		this->pos.x += this->vx;
		this->pos.y += this->vy;
		// nếu đang ở trạng thái beaten và hết thời gian của trạng thái beaten thì blue solder bị chết
		if (stateName == State::BEATEN&&timeCurrentState>=ENEMY_BEATEN_TIME)
			isDead = true;
		auto shield = Shield::getInstance();
		//nếu bị shield đánh chuyển sang beaten---> test 
		if (Collision::getInstance()->IsCollide(shield->getBoundingBox(), this->getBoundingBox()) && shield->state == Shield::ShieldState::Attack)
			ChangeState(State::BEATEN);
		this->curentAnimation->Update(dt);
		//tùy theo trạng thái hiện tại mà thay đổi trạng thái
		switch (this->stateName)
		{
		case State::DUCKING:
			if (timeCurrentState >= BLUE_SOLDER_DUCKING_TIME)
			{
				ChangeState(State::STANDING);
			}
			else
			{
				timeCurrentState += dt;
			}
			break;
		case State::STANDING:
			if (timeCurrentState < BLUE_SOLDER_STANDING_TIME)
			{
				if (timeCurrentState + dt >= BLUE_SOLDER_STANDING_TIME / 2 && timeCurrentState < BLUE_SOLDER_STANDING_TIME / 2)
				{
					auto bullet = new BulletSolder();
					bullet->existTime = 0;
					bullet->direction = this->direction;
					bullet->pos.y = this->getBoundingBox().top - 4;
					bullet->pos.x = this->pos.x;
					additionalObjects.push_back(bullet);
				}
				timeCurrentState += dt;
			}
			else
			{
				if(runType==RunType::NOTRUN)
					ChangeState(State::DUCKING);
				else
				{
					ChangeState(State::RUNNING);
				}
			}
			break;
		case State::RUNNING:
			if (canJump)
			{
				if (shield->state == Shield::ShieldState::Attack&&shield->direction != this->direction)
					this->vy = 2;
			}
			if (timeCurrentState > BLUE_SOLDER_RUNNING_TIME)
			{
				if (runType == RunType::CANRUN)
					ChangeState(State::STANDING);
			}
			else
			{
				timeCurrentState += dt;
			}	
			break;
		default:
			timeCurrentState += dt;
			break;
		}
	}

}

void Solder::Render()
{
	if (!isDead)
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		switch (this->direction)
		{
		case Player::MoveDirection::LeftToRight:
			this->curentAnimation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
			break;
		case Player::MoveDirection::RightToLeft:
			this->curentAnimation->Render(pos);
			break;
		default:
			break;
		}
	}
}


void Solder::LoadAllAnimation()
{
	animations[State::RUNNING] = new Animation(Tag::BLUESOLDIER, 0, 3);// run
	animations[State::STANDING] = new Animation(Tag::BLUESOLDIER, 3);//stand
	animations[State::DUCKING] = new Animation(Tag::BLUESOLDIER, 4);//duck
	animations[State::BEATEN] = new Animation(Tag::BLUESOLDIER, 5);//beaten
}

void Solder::ChangeState(State stateName)
{
	
	switch (stateName)
	{
	case State::STANDING:
		this->curentAnimation = animations[State::STANDING];
		this->vx = 0;
		isDead = false;
		break;
	case State::RUNNING:
		this->curentAnimation = animations[State::RUNNING];
		if (this->direction == Player::MoveDirection::LeftToRight)
			this->vx = ENEMY_SPEED* PLAYER_NORMAL_SPEED;
		else
			this->vx = -ENEMY_SPEED*PLAYER_NORMAL_SPEED;
		isDead = false;
		break;
	case State::DUCKING:
		this->curentAnimation = animations[State::DUCKING];
		this->vx = 0;
		isDead = false;
		break;
	case State::BEATEN:
		this->curentAnimation = animations[State::BEATEN];
		this->vx = this->vy = 0;
		if (this->direction == Player::MoveDirection::LeftToRight)
			this->pos.x -= 3;
		else
		{
			this->pos.x += 3;
		}
		break;
	default:
		break;
	}
	this->stateName = stateName;
	timeCurrentState = 0;
}
