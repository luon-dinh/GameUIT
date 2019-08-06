#pragma once
#include "Global.h"
#include <d3d9.h>
#include <d3dx9.h>

const long cameraSpeed = 1;

class Camera
{
private:
	//Toạ độ bounding box cho việc dời camera thường.
	//Toạ độ này là từ màn hình vào 4 cạnh của camera.
	const int topBound = 40;
	const int bottomBound = 88;
	const int leftBound = 70;
	const int rightBound = 135;

	const int topCriticalLine = 20;
	const int bottomCriticalLine = 40;
	
	//Toạ độ bounding box cho việc dời camera nâng cao.
	const int topBoundAdvanced = 60;
	const int bottomBoundAdvanced = 60;
	const int leftBoundAdvanced = 70;
	const int rightBoundAdvanced = 145;

	//Thời gian delay tối đa của camera khi đụng Critical Line (tính bằng ms).
	//Tức là trong khoảng thời gian này là camera phải lết được lên đến player.
	const int timeDelay = 500;

	//Giới hạn pixel di chuyển tối đa trong 1 frame.
	const int maxMoveLength = 999;

	//DeltaX,Y dùng để set vị trí tương lai của player.
	int DeltaX = 0;
	int DeltaY = 0;

	Camera();
	~Camera();
	long topLeftX;
	long topLeftY;
	long width;
	long height;
	long mapHeight;
	long mapWidth;

	//Biến dùng để giữ trạng thái khoá của Camera.
	bool isCameraLocked = false;

	int leftBoundTemp = leftBound;
	int rightBoundTemp = rightBound;

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

	//Di chuyển camera có delay.
	void UpdateCameraWithDelay(double dt);

	//Cài đặt vị trí cho Camera.
	void SetPosition(float x, float y);

	//Cài đặt vị trí cho Camera dựa vào CameraInfo.
	void SetPosition(CameraInfo camInfo)
	{
		this->topLeftX = camInfo.topLeftX;
		this->topLeftY = camInfo.topLeftY;
	}

	//Lấy vị trí hiện tại của Camera.
	CameraInfo GetCurrentCameraPosition()
	{
		CameraInfo camInfo;
		camInfo.topLeftX = this->topLeftX;
		camInfo.topLeftY = this->topLeftY;
		return camInfo;
	}

	//Cài đặt vị trí tương lai cho Camera (camera sẽ di chuyển trong khoảng thời gian timeDelay đến vị trí tương lai đã set).
	void SetPositionWithDelay(float x, float y);

	//Cài đặt kích thước của Camera.
	void SetMapProperties(long height, long width);

	//Lấy vector dùng để vẽ Map lên màn hình D3D (thường là vị trí 0,0,0).
	D3DXVECTOR3 getPositionVector();
	//Lấy BOUND (BOUND này dùng để giới hạn lại phạm vi của player trước khi camera di chuyển).
	RECT getBoundingBox();

	//Lấy ra Critical Line trên.
	int getTopCriticalLine() { return topCriticalLine; };

	//Lấy ra Critical Line dưới.
	int getBottomCriticalLine() { return bottomCriticalLine; };

	//Lấy BOUND dùng cho việc dịch camera nâng cao.
	RECT getBoundingBoxAdvanced();

	//Hàm dùng để reset lại toạ độ của camera khi vào map mới.
	void ResetCameraPosition() { topLeftX = 0, topLeftY = SCREEN_HEIGHT; }

	//Hàm này sẽ hỗ trợ chuyển từ WorldPort sang ViewPort
	D3DXVECTOR3 convertWorldToViewPort(D3DXVECTOR3 worldPortPos);
	Camera(Camera*);

	//Hàm dùng để khoá camera.
	void LockCamera();
	void UnlockCamera();
	bool GetCameraLockState() { return isCameraLocked; }
};