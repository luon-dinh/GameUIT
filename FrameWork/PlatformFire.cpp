#include "PlatformFire.h"
#include "Camera.h"

PlatformFire::PlatformFire(PlatformFireDirection _direction, int posX, int posY)
{
	fireDirection = _direction;
	this->pos.x = posX;
	this->pos.y = posY;
	LoadAllAnimation();
	if (_direction == PlatformFireDirection::LEFTTORIGHT || _direction == PlatformFireDirection::RIGHTTOLEFT)
		currentAnim = jetHorizontal;
	else if (_direction == PlatformFireDirection::TOPTOBOTTOM)
		currentAnim = jetVertical;
}

PlatformFire::~PlatformFire()
{
	if (jetVertical != nullptr)
		delete jetVertical;
	if (jetHorizontal != nullptr)
		delete jetHorizontal;
}

void PlatformFire::LoadAllAnimation()
{
	jetVertical = new Animation(Tag::MOVING_PLATFORM_VERTICAL_FIRE, 0, 2, fireDelay);
	jetHorizontal = new Animation(Tag::MOVING_PLATFORM_HORIZONTAL_FIRE, 0, 2, fireDelay);
}

void PlatformFire::SetFirePosition(int posX, int posY)
{
	this->pos.x = posX;
	this->pos.y = posY;
}

void PlatformFire::Update(float dt)
{
	currentAnim->Update(dt);
}

void PlatformFire::Render()
{
	D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));
	D3DXVECTOR2 viewPortPos2(viewPort.x, viewPort.y);
	if (fireDirection == PlatformFireDirection::LEFTTORIGHT)
		currentAnim->Render(viewPortPos2, TransformationMode::FlipHorizontal);
	else
		currentAnim->Render(viewPortPos2);
	//if (fireDirection == PlatformFireDirection::LEFTTORIGHT)
	//	currentAnim->Render(viewPort, TransformationMode::FlipHorizontal);
	//else
	//	currentAnim->Render(viewPort);
}