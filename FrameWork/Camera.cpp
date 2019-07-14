#include "Camera.h"

Camera* Camera::instance = NULL;

Camera* Camera::GetInstance()
{
	if (instance == NULL)
		instance = new Camera();
	return instance;
}

Camera::Camera()
{
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
}

Rect Camera::GetRect()
{
	return Rect(x, y, width, height);
}

void Camera::Update(Rect mapRect)
{
	if (this->x <= 0)
	{
		this->x = 0;
	}


	else if (this->x >= mapRect.width - this->width)
	{
		this->x = mapRect.width - this->width;
	}
}

void Camera::ConvertPositionToViewPort(float& x, float& y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -this->x;
	matrix._42 = this->y;
	D3DXVECTOR4 MatrixResult;
	D3DXVec2Transform(&MatrixResult, &D3DXVECTOR2(x, y), &matrix);
	x = MatrixResult.x;
	y = MatrixResult.y;
}
