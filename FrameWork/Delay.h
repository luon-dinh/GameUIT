#pragma once

//Class này nhằm mục đích giúp quản lý delay dễ dàng hơn.
class Delay
{
	float delayInterval;
	float currentTick;
public:
	Delay(float _delayInterval);
	//Nếu đã đủ khoảng thời gian delay, hàm này sẽ trả về true, đồng thời chỉnh lại biến đếm currentTick = 0.
	//Ngược lại, nếu chưa đủ thời gian delay, hàm này sẽ trả về false, và cộng dồn biến đếm currentTick với dt.
	bool GetDelayStatus(float dt);
};