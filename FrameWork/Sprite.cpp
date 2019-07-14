#include"Sprite.h"

void Sprite::Render(float x, float y)
{
	texture = TextureManager::getInstance()->getTexture(this->tag);
	auto position = D3DXVECTOR3(x,y,0);
	spriteHandler->Draw(texture, &this->rect, &center, &position, D3DCOLOR_XRGB(255, 255, 255));
}

void Sprite::Render(D3DXVECTOR2 pos)
{
	texture = TextureManager::getInstance()->getTexture(this->tag);
	spriteHandler->Draw(texture, &this->rect, &center, &D3DXVECTOR3(pos.x,pos.y,0), D3DCOLOR_XRGB(255, 255, 255));
}


Sprite::Sprite(Tag tag, int top, int left, int bottom, int right)
{
	this->tag = tag;
	this->texture = TextureManager::getInstance()->getTexture(tag);
	this->rect.top = top;
	this->rect.bottom = bottom;
	this->rect.left = left;
	this->rect.right = right;
	center = D3DXVECTOR3((right -left) / 2, (bottom -top) / 2, 0);
}
