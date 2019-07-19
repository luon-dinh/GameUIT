#pragma once
#include "Global.h"
#include <d3d9.h>
#include <d3dx9.h>

const auto cameraSpeed = 1;

class Camera
{
private:
	//Toạ độ bounding box cho việc dời camera thường.
	//Toạ độ này là từ màn hình vào 4 cạnh của camera.
	const int topBound = 128;
	const int bottomBound = 88;
	const int leftBound = 70;
	const int rightBound = 135;

	const int topCriticalLine = 50;
	const int bottomCriticalLine = 20;
	
	//Toạ độ bounding box cho việc dời camera nâng cao.
	const int topBoundAdvanced = 60;
	const int bottomBoundAdvanced = 60;
	const int leftBoundAdvanced = 70;
	const int rightBoundAdvanced = 145;

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

	//Lấy BOUND dùng cho việc dịch camera nâng cao.
	RECT getBoundingBoxAdvanced();

	//Hàm dùng để reset lại toạ độ của camera khi vào map mới.
	void ResetCameraPosition() { topLeftX = 0, topLeftY = SCREEN_HEIGHT; }

	//Hàm này sẽ hỗ trợ chuyển từ WorldPort sang ViewPort
	D3DXVECTOR3 convertWorldToViewPort(D3DXVECTOR3 worldPortPos);
	Camera(Camera*);
};