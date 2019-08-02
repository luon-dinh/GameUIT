#include"Sprite.h"

void Sprite::Render(float x, float y, D3DCOLOR color)
{
	texture = TextureManager::getInstance()->getTexture(this->tag);
	spriteHandler->Draw(texture, &this->rect, &center, &D3DXVECTOR3(x,y,0), color);
}

void Sprite::Render(D3DXVECTOR2 position, D3DCOLOR color)
{
	texture = TextureManager::getInstance()->getTexture(this->tag);
	spriteHandler->Draw(texture, &this->rect, &center, &D3DXVECTOR3(position.x, position.y, 0) , color);
}

void Sprite::Render(D3DXVECTOR3 pos, D3DCOLOR color)
{
	Render(D3DXVECTOR2(pos.x, pos.y));
}



Sprite::Sprite(Tag _tag, int top, int left, int bottom, int right)
{
	this->tag = _tag;
	this->texture = TextureManager::getInstance()->getTexture(tag);
	this->rect.top = bottom;
	this->rect.bottom = top;
	this->rect.left = left;
	this->rect.right = right;
	center = D3DXVECTOR3((right -left) / 2, (top - bottom) / 2, 0);
}

#pragma region Transformation Draw  - Minhnd
void Sprite::_GetCenter2(D3DXVECTOR2* center) {
	center->x = this->center.x;
	center->y = this->center.y;
}

void Sprite::Render(TransformationMode transMode, float scaleRatio, D3DXVECTOR2 pos, D3DCOLOR color) {
	D3DXMATRIX matrix;
	switch (transMode) {
	case TransformationMode::FlipHorizontal:  _FlipHorizontal(&matrix); break;
	case TransformationMode::FlipVertical:    _FlipVertical(&matrix);break;
	case TransformationMode::Rotate180Degree: _Rotate180Degree(&matrix);break;
	case TransformationMode::Scale:			  _Scale(scaleRatio, &matrix);break;
	}
	_InnerRender(&matrix, pos, color);
}

void Sprite::Render(float scaleRatioX, float scaleRatioY, D3DXVECTOR2 pos, D3DCOLOR color) {
	D3DXMATRIX scaleMatrix;
	_Scale(scaleRatioX, scaleRatioY, &scaleMatrix);
	D3DXMATRIX mOld;
	spriteHandler->GetTransform(&mOld);
	spriteHandler->SetTransform(&scaleMatrix);
	spriteHandler->Draw(texture, &this->rect, &center, &D3DXVECTOR3(pos.x - (rect.right - rect.left) ,pos.y, 0), color);
	spriteHandler->SetTransform(&mOld);
}

void Sprite::_FlipHorizontal(D3DXMATRIX* matrix) {
	D3DXVECTOR2 flip = D3DXVECTOR2(-1, 1);
	D3DXVECTOR2 center;
	_GetCenter2(&center);
	D3DXMatrixTransformation2D(matrix, &center, 0, &flip, &center, 0, NULL);
}

void Sprite::_FlipVertical(D3DXMATRIX* matrix) {
	D3DXVECTOR2 flip = D3DXVECTOR2(1, -1);
	D3DXVECTOR2 center;
	_GetCenter2(&center);
	D3DXMatrixTransformation2D(matrix, &center, 0, &flip, NULL, 0, NULL);
}

void Sprite::_Rotate180Degree(D3DXMATRIX* matrix) {
	D3DXVECTOR2 flip = D3DXVECTOR2(1, -1);
	D3DXVECTOR2 center;
	_GetCenter2(&center);
	D3DXMatrixTransformation2D(matrix, &center, 0, &flip, &center, 3.14f, NULL);
}

void Sprite::_Scale(float ratio, D3DXMATRIX* matrix) {
	D3DXVECTOR2 scaleMatrix = D3DXVECTOR2(ratio, ratio);
	D3DXVECTOR2 center;
	_GetCenter2(&center);
	D3DXMatrixTransformation2D(matrix, &center, 0, &scaleMatrix, NULL, 0, NULL);
}

void Sprite::_Scale(float ratioX, float ratioY, D3DXMATRIX* matrix) {
	D3DXVECTOR2 scaleMatrix = D3DXVECTOR2(ratioX, ratioY);
	D3DXVECTOR2 center;
	_GetCenter2(&center);
	D3DXMatrixTransformation2D(matrix, &center, 0, &scaleMatrix, NULL, 0, NULL);
}

void Sprite::_InnerRender(D3DXMATRIX* matrix, D3DXVECTOR2 position, D3DCOLOR color) {
	D3DXMATRIX mOld;
	spriteHandler->GetTransform(&mOld);
	spriteHandler->SetTransform(matrix);
	spriteHandler->Draw(texture, &this->rect, &center, &D3DXVECTOR3(-position.x + (this->rect.right - this->rect.left), position.y, 0), color);
	spriteHandler->SetTransform(&mOld);
}
#pragma endregion
