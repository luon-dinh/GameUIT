#include"Object.h"

BoundingBox Object::getBoundingBox()
{
	BoundingBox box;
	box.top=this->pos.y-this->getHeight()/2;
	box.left = this->pos.x-this->getWidth()/2;
	box.right = box.left + this->getWidth();
	box.bottom = box.top + this->getHeight();
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

