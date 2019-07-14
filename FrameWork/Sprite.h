#pragma once
#include"Global.h"
#include"TextureManager.h"
#include"Collision.h"

class Sprite {
protected:
	LPDIRECT3DTEXTURE9 texture;
	RECT rect;
	D3DXVECTOR3 center;
public:
	Sprite(Tag tag, int top, int left, int bottom, int right);

	Sprite() {};
	virtual void Render(float x, float y);
	virtual void Render(D3DXVECTOR2 pos);
	virtual void Render(D3DXVECTOR3 pos);
	Tag tag;

	float posX;
	float posY;

	RECT getRECT()
	{
		return this->rect;
	}

};