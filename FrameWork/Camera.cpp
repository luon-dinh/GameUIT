#include "Camera.h"
#include "Player.h"
#include "Debug.h"

Camera* Camera::cameraInstance = nullptr;

void Camera::UpdateCameraWithDelay(double dt)
{

}

void Camera::SetPositionWithDelay(float x, float y)
{

}

Camera::Camera()
{
	long _x = 0;
	long _y = SCREEN_HEIGHT;
	topLeftX = _x;
	topLeftY = _y;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
}

Camera::Camera(Camera * anotherCam)
{
	topLeftX = anotherCam->topLeftX;
	topLeftY = anotherCam->topLeftY;
	width = anotherCam->width;
	height = anotherCam->height;
}

RECT Camera::getBoundingBox()
{
	RECT boundBox;
	boundBox.top = topBound;
	boundBox.left = leftBound;
	boundBox.right = rightBound;
	boundBox.bottom = bottomBound;
	return boundBox;
}

RECT Camera::getBoundingBoxAdvanced()
{
	RECT boundBox;
	boundBox.top = topBoundAdvanced;
	boundBox.bottom = bottomBoundAdvanced;
	boundBox.left = leftBoundAdvanced;
	boundBox.right = rightBoundAdvanced;
	return boundBox;
}

Camera::~Camera()
{

}


void Camera::ReleaseCameraInstance()
{
	if (cameraInstance != nullptr)
		delete cameraInstance;
}

Camera* Camera::getCameraInstance()
{
	if (cameraInstance == nullptr)
		cameraInstance = new Camera();
	return cameraInstance;
}


void Camera::SetPosition(float x, float y)
{
	topLeftX = x;
	topLeftY = y;
}

void Camera::MoveLeft(long s)
{
	if (isCameraLocked)
		return;
	if (topLeftX - s < 0)
		topLeftX = 0;
	else
		topLeftX -= s;
}

void Camera::MoveRight(long s)
{
	if (isCameraLocked)
		return;
	if (topLeftX + SCREEN_WIDTH + s >= mapWidth)
		topLeftX = mapWidth - SCREEN_WIDTH;
	else
		topLeftX += s;
}

void Camera::MoveUp(long s)
{
	if (isCameraLocked)
		return;
	if (topLeftY + s >= mapHeight)
		topLeftY = mapHeight;
	else
		topLeftY += s;
}

void Camera::MoveDown(long s)
{
	if (isCameraLocked)
		return;
	if (topLeftY - SCREEN_HEIGHT - s < 0)
		topLeftY = SCREEN_HEIGHT;
	else
		topLeftY -= s;
}

RECT Camera::getCameraRECT()
{
	RECT res;
	res.top = topLeftY;
	res.left = topLeftX;
	res.right = topLeftX + SCREEN_WIDTH;
	res.bottom = res.top - SCREEN_HEIGHT;
	return res;
}

void Camera::SetMapProperties(long height, long width)
{
	mapHeight = height;
	mapWidth = width;
}

D3DXVECTOR3 Camera::getPositionVector()
{
	D3DXVECTOR3 position(0, 0, 0);
	return position;
}

D3DXVECTOR3 Camera::convertWorldToViewPort(D3DXVECTOR3 worldPortPos)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt); //Khởi tạo ma trận đơn vị. Các phần tử nằm trên
	//Đường chéo chính đều có giá trị là 1.
	mt._22 = -1.0f;
	mt._41 = -topLeftX;
	mt._42 = topLeftY;

	D3DXVECTOR4 vp_pos; //Vector dùng để chứa kết quả nhân ma trận.
	D3DXVec3Transform(&vp_pos, &worldPortPos, &mt); //Nhân ma trận.
	
	//Xong xuôi thì ta lấy kết quả thu được trả về.
	D3DXVECTOR3 viewPortPos(vp_pos.x, vp_pos.y, 0);
	return viewPortPos;
}

void Camera::LockCamera()
{
	isCameraLocked = true;
}

void Camera::UnlockCamera()
{
	isCameraLocked = false;
}