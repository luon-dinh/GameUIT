#include"Object.h"

BoundingBox Object::getBoundingBox()
{
	BoundingBox box;
	box.top=this->pos.y;
	box.left = this->pos.x;
	box.right = box.left + width;
	box.bottom = box.top + height;
	box.vx = this->vx;
	box.vy = this->vy;
	return box;
}

void Object::Render()
{
	
}

void Object::Update(float dt)
{

}

int Object::getWidth()
{
	return SpriteManager::getInstance()->getSprite(this->tag)->getRECT().right - SpriteManager::getInstance()->getSprite(this->tag)->getRECT().left;
}

int Object::getHeight()
{
	return SpriteManager::getInstance()->getSprite(this->tag)->getRECT().bottom - SpriteManager::getInstance()->getSprite(this->tag)->getRECT().top;
}

