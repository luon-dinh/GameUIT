#pragma once
#include "Object.h"
#include "Delay.h"


//DisappearingPlatform có bốn trạng thái :
/*
Trạng thái 1 : Chưa được player đụng vào. Lúc này isPlatformActivated = false, isCollidable = true và isSplitting = false;
Trạng thái 2 : Đã được kích hoạt (được player đụng vào) và đang đứng được. Lúc này isPlatformActivated = true, isCollidable = true và isSplitting = false.
Trạng thái 3 : Splitting. Lúc này isPlatformActivated = true, isCollidable = false và isSplitting = true.
Trạng thái 4 : Joining phase 1. Lúc này isPlatformActivated = true, isCollidable = false và isSplitting = false.
*/
class DisappearingPlatform : public Object
{
	//Khoảng thời gian delay để nó mở ra lần 1.
	const int firstTimeSplitDelayTime = 500;
	
	//Khoảng thời gian delay để nó mở ra lần 2.
	const int normalSplitDelayTime = 1500;

	//Khoảng thời gian delay để nó đóng lại (phase 1).
	const int joiningTimeDelayPhase1Time = 1300;

	//Khoảng thời gian delay để nó đóng lại (phase 2).
	const int joiningTimeDelayPhase2Time = 200;

	//Khoảng thời gian chớp chớp khi cục gạch đã bị split.
	const int flashingDelayTime = 60;

	//Kích thước của platform.
	const int platformWidth = 16;
	const int platformHeight = 8;

	//Biến dùng để điều khiển việc cho hoặc không cho phép vẽ.
	bool isRenderable = true;

	Delay* firstSplitDelay;
	Delay* normalSplitDelay;
	Delay* joiningTimeDelayPhase1;
	Delay* joiningTimeDelayPhase2;
	Delay* renderDelay;

	//Sprite dùng để lưu giữ hình ảnh của cục gạch.
	Sprite* brickSprite;

	//Biến dùng để xác định xem player đã va chạm với nó lần nào chưa.
	bool isPlatformActivated = false;
	//Biến dùng để xác định xem trạng thái hiện tại là gì (splitting hay joining).
	bool isSplitting = false;
	//Dùng biến isCollidable để xác định xem platform hiện tại có hitbox hay không.
public:
	DisappearingPlatform(int _posX, int _posY);
	~DisappearingPlatform();
	//Cấm không cho Grid xoá platform.
	void DeactivateObjectInGrid() override {};
	void Update(float dt) override;
	void Render() override;
	BoundingBox getBoundingBox() override;
};