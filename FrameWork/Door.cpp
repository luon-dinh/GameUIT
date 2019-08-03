#include "Door.h"
#include "SceneManager.h"

Door::Door(int posX, int posY)
{
	this->pos.x = posX;
	this->pos.y = posY;
	this->vx = this->vy = 0;
	LoadAllAnim();
}

Door::~Door()
{
	if (doorDarkAnim != nullptr)
		delete doorDarkAnim;
	if (doorLightAnim != nullptr)
		delete doorLightAnim;
}

void Door::LoadAllAnim()
{
	doorDarkAnim = new Animation(Tag::DOOR_DARK, 0, 4, openDoorAnimDelay);
	doorLightAnim = new Animation(Tag::DOOR_LIGHT, 0, 4, openDoorAnimDelay);
}


void Door::Update(float dt)
{
	SetAnimOnLightStatus();
	//Chặn không cho animation lặp lại.
	if (currentAnim->curframeindex != currentAnim->toframe - 1)
		currentAnim->Update(dt);
}

void Door::Render()
{
	D3DXVECTOR3 viewPort = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(this->pos.x, this->pos.y, 0));
	currentAnim->Render(viewPort);
}

void Door::SetAnimOnLightStatus()
{
	if (SceneManager::getInstance()->IsLightOn())
		currentAnim = doorLightAnim;
	else
		currentAnim = doorDarkAnim;
}

BoundingBox Door::getBoundingBox()
{
	BoundingBox box = Object::getBoundingBox();
	box.left += 5;
	box.right -= 5;
	box.vx = box.vy = 0;
	return box;
}