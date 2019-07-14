#include"Sprite.h"
#include"Camera.h"

void Sprite::Render(float x, float y)
{
	texture = TextureManager::getInstance()->getTexture(this->tag);
	auto position = D3DXVECTOR3(x,y,0);
	D3DXVECTOR3 pos=Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(position.x, position.y, 0));
	spriteHandler->Draw(texture, &this->rect, &center, &pos, D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::Render(D3DXVECTOR2 position)
{
	texture = TextureManager::getInstance()->getTexture(this->tag);
	D3DXVECTOR3 pos = Camera::getCameraInstance()->convertWorldToViewPort(D3DXVECTOR3(position.x, position.y, 0));
	spriteHandler->Draw(texture, &this->rect, &center, &pos, D3DCOLOR_XRGB(255, 255, 255));
}


Sprite::Sprite(Tag _tag, int top, int left, int bottom, int right)
{
	this->tag = _tag;
	this->texture = TextureManager::getInstance()->getTexture(tag);
	this->rect.top = top;
	this->rect.bottom = bottom;
	this->rect.left = left;
	this->rect.right = right;
	center = D3DXVECTOR3((right -left) / 2, (bottom -top) / 2, 0);
}
