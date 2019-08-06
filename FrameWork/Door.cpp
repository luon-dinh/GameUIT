#include "Door.h"
#include "SceneManager.h"

Door::Door(int posX, int posY)
{
	this->pos.x = posX;
	this->pos.y = posY;
	this->vx = this->vy = 0;
	this->tag = Tag::DOOR_DARK;
	delayDoorOpen = new Delay(openDoorTime);
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
	//Nếu cửa chưa được player chạm vào thì thôi, có gì đâu mà update.
	if (!isDoorActivated)
		return;
	//Chặn không cho animation lặp lại.
	if (currentAnim->curframeindex != currentAnim->toframe - 1)
		currentAnim->Update(dt);
	//Xem đã đủ thời gian chờ để qua màn khác chưa.
	if (delayDoorOpen->GetDelayStatus(dt))
	{
		isDoorActivated = false;
		currentAnim->curframeindex = 0;
		Player::getInstance()->UnlockInput();
		SceneManager::getInstance()->GoToNextScene();
	}
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
	box.left = this->pos.x - 5;
	box.right = this->pos.x + 5;
	box.top = this->pos.y + doorHeight / 2;
	box.bottom = this->pos.y - doorHeight / 2;
	box.vx = box.vy = 0;
	return box;
}

bool Door::OnRectCollided(Object* object, CollisionSide colSide)
{
	if (object->tag == Tag::PLAYER && KeyboardManager::getInstance()->getKeyPressedOnce(DIK_UP))
	{
		isDoorActivated = true;
		Player::getInstance()->LockInput();
		SoundManager::getinstance()->play(SoundManager::SoundName::door_open);
		return true;
	}
	return false;
}