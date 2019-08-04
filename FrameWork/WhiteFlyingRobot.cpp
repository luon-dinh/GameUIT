#include "WhiteFlyingRobot.h"
#include "SceneManager.h"
#include "Debug.h"

WhiteFlyingRobot::WhiteFlyingRobot(int posX, int posY)
{
	this->tag = Tag::WHITEFLYINGROBOT;
	this->direction = MoveDirection::LeftToRight;
	LoadAllAnimation();
	player = Player::getInstance();
	robotState = State::FLYING;
	currentAnimation = stateAnim[robotState];
	this->pos.x = posX;
	this->pos.y = posY;
	isDead = false;
	health = 2;
}

WhiteFlyingRobot::~WhiteFlyingRobot()
{
	//Xoá sạch map.
	for (auto anim : stateAnim)
		delete anim.second;
}

void WhiteFlyingRobot::EnemyDeadUpdate(double dt)
{
	PrintDebug("\nCurrentStateTime : ");
	PrintDebugNumber(currentStateTime);
	if (robotState == State::DEAD) //Nổ tung và deactivate nó.
	{
		if (currentStateTime > explodeTime)
		{
			DeactivateObjectInGrid();
			return;
		}
	}
	else //Trạng thái falling.
	{
		//Nếu đang trong trạng thái falling thì ta cho nó rơi xuống đến khi đụng đất.
		this->vx = 0;
		this->vy = -1;
		this->pos.x += this->vx;
		this->pos.y += this->vy;
	}
	
	this->currentAnimation->Update(dt);
}

void WhiteFlyingRobot::EnemyAliveUpdate(double dt)
{
	delayTime += dt;

	if (delayTime < delayFlyingTime)
		return;
	delayTime = 0;
	//Mỗi lần xoay 1 góc 1 độ.
	currentDegree = fmod(currentDegree + angularVelocity, 360);

	auto inRange = [](double value, double realValue) {return (value - 1 <= realValue) && (realValue <= value + 1); };

	//Quái chỉ bắn khi ở góc 0 độ và góc 90 độ.
	if (inRange(0, currentDegree) || inRange(90, currentDegree))
	{
		ChangeState(State::ATTACK);
	}

	//Cập nhật lại tốc độ bay hiện tại dựa vào góc.
	auto convertToRad = [](double degree) {return degree * PI / 180; };
	this->vx = cos(convertToRad(currentDegree)) * VXMax;
	this->vy = -sin(convertToRad(currentDegree)) * VYMax;
	//Cập nhật lại phương hướng (hướng trái hay phải) của enemy.
	if (player->pos.x > this->pos.x)
		this->direction = MoveDirection::LeftToRight;
	else
		this->direction = MoveDirection::RightToLeft;
	//Cập nhật lại vị trí theo tốc độ.
	this->pos.x += this->vx;
	this->pos.y += this->vy;
	//Cập nhật animation.
	this->currentAnimation->Update(dt);
}

void WhiteFlyingRobot::EnemyAttackingUpdate(double dt)
{
	if (currentStateTime > delayAttackingAnim * 2)
	{
		int bulletX = (this->direction == MoveDirection::LeftToRight) ? (this->pos.x + 5) : (this->pos.x - 5);
		int bulletY = this->pos.y;
		SceneManager::getInstance()->AddObjectToCurrentScene(new BulletWhiteFlyingRocketer(this->direction, bulletX, bulletY));
		ChangeState(State::FLYING);
	}
	//Cập nhật lại phương hướng (hướng trái hay phải) của enemy.
	if (player->pos.x > this->pos.x)
		this->direction = MoveDirection::LeftToRight;
	else
		this->direction = MoveDirection::RightToLeft;
	currentAnimation->Update(dt);
}

void WhiteFlyingRobot::EnemyBeatenUpdate(double dt)
{
	//Nếu đã hết thời gian beaten  thì ta quay lại trạng thái bay bình thường.
	if (currentStateTime > beatenTime)
	{
		ChangeState(State::FLYING);
		isCollidable = true;
	}		
	currentBeatenTick = fmod((currentBeatenTick + dt), delayBeatenSprite);
	isCollidable = false;
	EnemyAliveUpdate(dt);
}

void WhiteFlyingRobot::Update(float dt)
{
	currentStateTime += dt;
	//Xét từng state.
	if (robotState == State::FLYING)
		EnemyAliveUpdate(dt);

	else if (robotState == State::ATTACK)
		EnemyAttackingUpdate(dt);

	else if (robotState == State::BEATEN)
		EnemyBeatenUpdate(dt);

	else if (robotState == State::FALLING || robotState == State::DEAD)
		EnemyDeadUpdate(dt);
}

void WhiteFlyingRobot::Render()
{
	//Nếu đang ở trạng thái beaten mà thời gian chưa đủ để render tiếp thì không render.
	if (robotState == State::BEATEN && currentBeatenTick < delayBeatenSprite/2)
	{
		return;
	}

	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
	switch (this->direction)
	{
	case Player::MoveDirection::LeftToRight:
		this->currentAnimation->Render(D3DXVECTOR2(pos), TransformationMode::FlipHorizontal);
		break;
	case Player::MoveDirection::RightToLeft:
		this->currentAnimation->Render(pos);
		break;
	default:
		break;
	}
}

void WhiteFlyingRobot::LoadAllAnimation()
{
	//Load animation tương ứng với trạng thái.
	Animation* flyingAnim = new Animation(Tag::WHITEFLYINGROBOT, 0, 2, delayFlyingSprite);
	Animation* fallingAnim = new Animation(Tag::WHITEFLYINGROBOT, 2, 4, delayFallingAnim);
	Animation* attackingAnim = new Animation(Tag::WHITEFLYINGROBOT, 4, 6, delayAttackingAnim);
	std::pair<State, Animation*> flyingPair(State::FLYING, flyingAnim);
	std::pair<State, Animation*> spinningPair(State::FALLING, fallingAnim);
	std::pair<State, Animation*> attackingPair(State::ATTACK, attackingAnim);
	stateAnim.insert(flyingPair);
	stateAnim.insert(spinningPair);
	stateAnim.insert(attackingPair);
}

void WhiteFlyingRobot::ChangeState(State state)
{
	currentStateTime = 0;
	switch (state)
	{
	case State::FLYING:
	case State::BEATEN:
		currentAnimation = stateAnim[State::FLYING];
		break;
	case State::FALLING:
		currentAnimation = stateAnim[State::FALLING];
		break;
	case State::DEAD:
		currentAnimation = explodeAnim;
		break;
	case State::ATTACK:
		currentAnimation = stateAnim[State::ATTACK];
		break;
	}
	robotState = state;
}

void WhiteFlyingRobot::OnCollision(Object* object, collisionOut* colout)
{
	Shield* shield = dynamic_cast<Shield*> (object);
	//Nếu vật đánh trúng enemy là shield.
	if (shield != nullptr)
	{
		if (shield->state == (Shield::ShieldState::Attack))
		{
			//Nếu không đang trong trạng thái beaten mới trừ máu.
			if (robotState != State::BEATEN)
				--health;
			if (health <= 0)
				ChangeState(State::FALLING);
			else
				ChangeState(State::BEATEN);
		}
	}
	//Nếu rơi trúng object tĩnh thì cho nổ tung.
	if (robotState == State::FALLING && object->tag == Tag::STATICOBJECT)
		ChangeState(State::DEAD);
}

bool WhiteFlyingRobot::OnRectCollided(Object* object, CollisionSide side)
{
	return true;
}

void WhiteFlyingRobot::OnNotCollision(Object* object)
{

}