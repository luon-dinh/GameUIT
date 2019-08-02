#pragma once
#include "Object.h"
class PlatformFire : public Object
{
public:
	enum PlatformFireDirection
	{
		RIGHTTOLEFT,
		LEFTTORIGHT,
		TOPTOBOTTOM
	};
private:
	//Khoảng thời gian giữa các lần phóng lửa.
	const int fireDelay = 120;

	PlatformFireDirection fireDirection;
	Animation* jetVertical;
	Animation* jetHorizontal;
	Animation* currentAnim;

	void LoadAllAnimation();
public:
	PlatformFire(PlatformFireDirection direction, int posX, int posY);
	~PlatformFire();
	void SetFirePosition(int posX, int posY);
	void Update(float dt) override;
	void Render() override;
};