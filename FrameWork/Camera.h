#pragma once
#include "Global.h"
#include <d3d9.h>
#include <d3dx9.h>

const auto cameraSpeed = 1;

class Camera
{
private:
	const int topBound = 128;
	const int bottomBound = 118;
	const int leftBound = 70;
	const int rightBound = 145;
	Camera();
	~Camera();
	long topLeftX;
	long topLeftY;
	long width;
	long height;
	long mapHeight;
	long mapWidth;

	static Camera * cameraInstance;

public:

	static Camera * getCameraInstance();

	void ReleaseCameraInstance();

	//Lấy phần RECT dùng để cắt Texture (toạ độ World trục y hướng lên).
	RECT getCameraRECT();

	//Di chuyển camera một đơn vị cameraSpeed.
	void MoveLeft(long = cameraSpeed);
	void MoveRight(long = cameraSpeed);
	void MoveUp(long = cameraSpeed);
	void MoveDown(long = cameraSpeed);

	//Cài đặt vị trí cho Camera.
	void SetPosition(float x, float y);

	//Cài đặt kích thước của Camera.
	void SetMapProperties(long height, long width);

	//Lấy vector dùng để vẽ Map lên màn hình D3D (thường là vị trí 0,0,0).
	D3DXVECTOR3 getPositionVector();
	//Lấy BOUND (BOUND này dùng để giới hạn lại phạm vi của player trước khi camera di chuyển).
	RECT getBoundingBox();

	//Hàm này sẽ hỗ trợ chuyển từ WorldPort sang ViewPort
	D3DXVECTOR3 convertWorldToViewPort(D3DXVECTOR3 worldPortPos);
	Camera(Camera*);
};