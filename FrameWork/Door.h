#pragma once
#include "Object.h"
#include "Delay.h"
class Door : public Object
{
	//Thời gian chuyển các frame trong việc mở cửa.
	const int openDoorAnimDelay = 4.0*1000/60;

	//Thời gian của việc mở cửa.
	const int openDoorTime = openDoorAnimDelay*4;

	Animation * doorDarkAnim;
	Animation * doorLightAnim;
	Animation * currentAnim;

	const int doorWidth = 32;
	const int doorHeight = 48;

	Delay* delayDoorOpen;

	//Biến kiểm tra player đã gọi đến việc mở cửa chưa.
	bool isDoorActivated = false;
public:
	Door(int posX, int posY);
	~Door();
	void Update(float dt) override;
	void Render() override;
	void LoadAllAnim();
	bool OnRectCollided(Object*, CollisionSide colSide) override;
	BoundingBox getBoundingBox() override;
	void DeactivateObjectInGrid() override {};
private:
	void SetAnimOnLightStatus();
};