#pragma once
#include"Global.h"
#include"TextureManager.h"
#include"Collision.h"

class Sprite {
protected:
	LPDIRECT3DTEXTURE9 texture;
	RECT rect;
	D3DXVECTOR3 center;
	float customRotate;

	void _FlipHorizontal(D3DXMATRIX* matrix);
	void _FlipVertical(D3DXMATRIX* matrix);
	void _Rotate180Degree(D3DXMATRIX* matrix);
	void _Rotate(D3DXMATRIX* matrix, float radian);
	void _Scale(float ratio, D3DXMATRIX* matrix);
	void _Scale(float ratioX, float ratioY, D3DXMATRIX* matrix);
	void _InnerRender(D3DXMATRIX* matrix, D3DXVECTOR2 position, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void _GetCenter2(D3DXVECTOR2* center2);

public:

	typedef enum {
		FlipHorizontal,
		FlipVertical,
		Rotate180Degree,
		Scale,
		CustomRotate
	} TransformationMode;


	Sprite(Tag tag, int top, int left, int bottom, int right);

	Sprite() {};

	void SetCustomRotateRadian(float radian);
	virtual void Render(float x, float y, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	virtual void Render(D3DXVECTOR2 pos, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	virtual void Render(D3DXVECTOR3 pos, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	virtual void Render(TransformationMode transMode, float scaleRatio, D3DXVECTOR2 pos, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	virtual void Render(float scaleRatioX, float scaleRatioY, D3DXVECTOR2 pos, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	Tag tag;

	float posX;
	float posY;

	RECT getRECT()
	{
		return this->rect;
	}

};