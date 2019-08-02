#include "Canon.h"


Canon::Canon() : Canon(RotateDirection::Left) {}

Canon::Canon(RotateDirection direction) {
	this->tag = Tag::CANON;
	this->type = Type::ENEMY;
	this->currentAnimation = new Animation(Tag::CANON, 0, 7, 10);
	this->isDead = false;
	this->SetVelocity(D3DXVECTOR2(0, 0));
	this->curFrameRotate = this->curFrameFire = 0;
	this->pos.x = 100;
	this->pos.y = 66;

	this->SetCanonDirection(direction);
}

Canon::~Canon() {

}


int Canon::GetCollisionDamage() {
	return 1;
}

void Canon::Update(float dt) {
	if (this->IsRotate()) {
		this->Rotate();
		this->currentAnimation->Update(dt);
		return;
	}

	Fire();
}

bool Canon::IsRotate() {
	return this->isRotate;
}

void Canon::Rotate() {
	this->curFrameRotate++;
	if (this->curFrameRotate > FRAME_PER_ROTATE) {
		this->curFrameRotate = 0;
		this->isRotate = false;
		this->isCollidable = true;
	}
}

void Canon::SetCanonDirection(Canon::RotateDirection direction) {
	this->rotateRadian = this->currentAnimation->curframeindex = direction;
}

void Canon::Fire() {
	this->curFrameFire++;
	if (this->curFrameFire < TIME_FIRE) {
		return;
	}
	this->curFrameFire = 0;

	Bullet* bullet = new BulletSolder(this->direction);
	bullet->vx = BULLET_SPEED;
	int corner = this->currentAnimation->curframeindex % 8;
	// hướng qua phải
	if (corner >= 0 && corner <= 4) {
		bullet->SetMoveDirection(MoveDirection::LeftToRight);
		if (corner == 0 || corner == 4) {
			bullet->vx = 0;
		}
	}
	else {
		// hướng qua trái
		bullet->SetMoveDirection(MoveDirection::RightToLeft);
	}

	if (corner == 2 || corner == 6){
		bullet->vy = 0;
	}
	else {
		if ((corner == 0) || (corner == 1) || (corner == 7)) {
			bullet->vy = BULLET_SPEED;
		}
		else {
			bullet->vy = -BULLET_SPEED;
		}
	}
	bullet->pos.x = this->pos.x + 2 * bullet->vx;
	bullet->pos.y = this->pos.y + 2 * bullet->vy;
	SceneManager::getInstance()->AddObjectToCurrentScene(bullet);
}

bool Canon::OnRectCollided(Object* object, CollisionSide side) {
	switch (object->tag) {
	case Tag::SHIELD: 
		if (this->IsRotate())
			return false;
		// khi va chạm shield thì rotate
		OnStartRotate();
		return true;
	}
	return false;
}

void Canon::OnStartRotate() {
	this->isRotate = true;
	this->isCollidable = false;
}

void Canon::Render() {
	if (!isDead)
	{
		D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos));
		this->currentAnimation->Render(pos);
	}
}