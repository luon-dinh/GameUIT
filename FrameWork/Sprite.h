#pragma once
#include"Global.h"
#include"TextureManager.h"
#include"Collision.h"

class Sprite {
protected:
	LPDIRECT3DTEXTURE9 texture;
	RECT rect;
	D3DXVECTOR3 center;

	void _FlipHorizontal(D3DXMATRIX* matrix);
	void _FlipVertical(D3DXMATRIX* matrix);
	void _Rotate180Degree(D3DXMATRIX* matrix);
	void _Scale(float ratio, D3DXMATRIX* matrix);
	void _InnerRender(D3DXMATRIX* matrix, D3DXVECTOR2 position);
	void _GetCenter2(D3DXVECTOR2* center2);

public:

	typedef enum {
		FlipHorizontal,
		FlipVertical,
		Rotate180Degree,
		Scale,
	} TransformationMode;


	Sprite(Tag tag, int top, int left, int bottom, int right);

	Sprite() {};
	virtual void Render(float x, float y);
	virtual void Render(D3DXVECTOR2 pos);
	virtual void Render(D3DXVECTOR3 pos);
	virtual void Render(TransformationMode transMode, float scaleRatio, D3DXVECTOR2 pos);
	Tag tag;

	float posX;
	float posY;

	RECT getRECT()
	{
		return this->rect;
	}

};